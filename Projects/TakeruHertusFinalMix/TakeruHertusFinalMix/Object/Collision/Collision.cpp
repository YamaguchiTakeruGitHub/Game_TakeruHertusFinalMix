#include "Collision.h"
#include <math.h>

void Collision::ClosestPointsOnSegments(VECTOR A1, VECTOR A2, VECTOR B1, VECTOR B2, VECTOR& closestA, VECTOR& closestB)
{
	VECTOR dA = VSub(A2, A1);
	VECTOR dB = VSub(B2, B1);
	VECTOR r = VSub(A1, B1);

	float a = VDot(dA,dA);
	float e = VDot(dB, dB);
	float f = VDot(r, r);

	float s, t;
	if (a <= 1e-6 && e <= 1e-6) {
		s = t = 0.0f;
	}
	else if (a <= 1e-6) {
		t = Clamp(f / e, 0.0f, 1.0f);
		s = 0.0f;
	}
	else {
		float c = VDot(dA,r);
		if (e <= 1e-6) {
			s =Clamp(-c / a, 0.0f, 1.0f);
			t = 0.0f;
		}
		else {
			float b = VDot(dA,dB);
			float denom = a * e - b * b;

			if (denom != 0.0f) {
				s = Clamp((b * f - c * e) / denom, 0.0f, 1.0f);
			}
			else {
				s = 0.0f;
			}

			t = (b * s + f) / e;

			if (t < 0.0f) {
				t = 0.0f;
				s = Clamp(-c / a, 0.0f, 1.0f);
			}
			else if (t > 1.0f) {
				t = 1.0f;
				s = Clamp((b - c) / a, 0.0f, 1.0f);
			}
		}
	}
	

	closestA = VAdd(A1, VScale(dA,s));
	closestB = VAdd(B1, VScale(dB, t));
	
}

bool Collision::CheckSphereHitCollision(VECTOR _pos1, float _r1, VECTOR _pos2, float _r2)
{
	VECTOR delta = VSub(_pos1, _pos2);
	float distanceSquared = VSize(delta);
	float radiusSum = _r1 + _r2;

	return distanceSquared <= radiusSum;
}

VECTOR Collision::CheckSphereResolveCollision(VECTOR _pos1, float _r1, VECTOR _pos2, float _r2)
{
	VECTOR p1Top2 = VSub(_pos1, _pos2);
	float length = VSize(p1Top2);
	if (length > 0)
	{
		p1Top2 = VScale(p1Top2, 1.0f / length);
	}
	float pushDistance = 8.0f;
	VECTOR pushVector = VScale(p1Top2, pushDistance);

	return VSub(_pos2, pushVector);
}

bool Collision::CheckBoxHitCollision(VECTOR _spherePos, float _sphereRadius, VECTOR _boxPos, VECTOR _boxSize)
{
	VECTOR closestPoint = _spherePos;
	closestPoint.x = max(_boxPos.x - _boxSize.x / 2, min(_spherePos.x, _boxPos.x + _boxSize.x / 2));
	closestPoint.y = max(_boxPos.y - _boxSize.y / 2, min(_spherePos.y, _boxPos.y + _boxSize.y / 2));
	closestPoint.z = max(_boxPos.z - _boxSize.z / 2, min(_spherePos.z, _boxPos.z + _boxSize.z / 2));
	//
	//VECTOR diff = VSub(_spherePos, closestPoint);
	//float distSq = VDot(diff, diff);//ベクトルのない席

	//if (distSq < _sphereRadius * _sphereRadius)
	//{
	//	float dist = sqrtf(distSq);
	//	return true;
	//}

	//return false;
	VECTOR distance = VSub(_spherePos, closestPoint);
	//float distansSquared = VSize(distance);
	//return distansSquared <= _sphereRadius;

	float distansSquared = VDot(distance, distance);
	return distansSquared < _sphereRadius * _sphereRadius;


}

VECTOR Collision::CheckBoxResolveCollision(VECTOR _spherePos, float _sphereRadius, VECTOR _boxPos, VECTOR _boxSize)
{
	VECTOR boxMin = VSub(_boxPos, VGet(_boxSize.x / 2, _boxSize.y / 2, _boxSize.z / 2));
	VECTOR boxMax = VAdd(_boxPos, VGet(_boxSize.x / 2, _boxSize.y / 2, _boxSize.z / 2));

	// ボックスの最近接点を求める
	VECTOR boxClosest = VGet(
		max(boxMin.x, min(_spherePos.x, boxMax.x)),
		max(boxMin.y, min(_spherePos.y, boxMax.y)),
		max(boxMin.z, min(_spherePos.z, boxMax.z))
	);

	// 球の中心と最近接点の距離
	VECTOR diff = VSub(_spherePos, boxClosest);
	float distSq = VDot(diff, diff);  // 二乗距離

	// 衝突判定
	float radiusSq = _sphereRadius * _sphereRadius;
	if (distSq < radiusSq)
	{
		float dist = std::sqrt(distSq);
		VECTOR normal = (dist > 0.0f) ? VScale(diff, 1.0f / dist) : VGet(1.0f, 0.0f, 0.0f); // 正規化

		// 押し戻し処理
		float overlap = _sphereRadius - dist;
		VECTOR pushBack = VScale(normal, overlap);

		return VAdd(_spherePos, pushBack);
	}

	return _spherePos; // 変化なし
}

//bool Collision::CapsuleCollisionCheck(VECTOR A1, VECTOR A2, float r1, VECTOR B1, VECTOR B2, float r2)
//{
//	VECTOR closestA, closestB;
//	ClosestPointsOnSegments(A1, A2, B1, B2, closestA, closestB);
//
//	float distanceSquared = VSize(VSub(closestA, closestB));
//}

void Collision::CapsuleResolveCollision(VECTOR& A1, VECTOR& A2, float r1, VECTOR& B1, VECTOR& B2, float r2)
{
}

void Collision::DrawBox3D(VECTOR _boxPos, VECTOR _boxSize)
{
	VECTOR corners[8];
	corners[0] = VGet(_boxPos.x - _boxSize.x / 2, _boxPos.y - _boxSize.y / 2, _boxPos.z - _boxSize.z / 2);
	corners[1] = VGet(_boxPos.x + _boxSize.x / 2, _boxPos.y - _boxSize.y / 2, _boxPos.z - _boxSize.z / 2);
	corners[2] = VGet(_boxPos.x + _boxSize.x / 2, _boxPos.y + _boxSize.y / 2, _boxPos.z - _boxSize.z / 2);
	corners[3] = VGet(_boxPos.x - _boxSize.x / 2, _boxPos.y + _boxSize.y / 2, _boxPos.z - _boxSize.z / 2);
	corners[4] = VGet(_boxPos.x - _boxSize.x / 2, _boxPos.y - _boxSize.y / 2, _boxPos.z + _boxSize.z / 2);
	corners[5] = VGet(_boxPos.x + _boxSize.x / 2, _boxPos.y - _boxSize.y / 2, _boxPos.z + _boxSize.z / 2);
	corners[6] = VGet(_boxPos.x + _boxSize.x / 2, _boxPos.y + _boxSize.y / 2, _boxPos.z + _boxSize.z / 2);
	corners[7] = VGet(_boxPos.x - _boxSize.x / 2, _boxPos.y + _boxSize.y / 2, _boxPos.z + _boxSize.z / 2);

	for (int i = 0; i < 4; i++)
	{
		DrawLine3D(corners[i], corners[(i + 1) % 4], 0xff0000);
		DrawLine3D(corners[i + 4], corners[(i + 1) % 4 + 4], 0xff0000);
		DrawLine3D(corners[i], corners[i + 4], 0xff0000);
	}

}
