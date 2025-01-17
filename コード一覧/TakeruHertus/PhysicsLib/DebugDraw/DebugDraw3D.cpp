#include "DebugDraw3D.h"

std::vector<DebugDraw3D::SphereInfo>  DebugDraw3D::sphereInfo;
std::vector<DebugDraw3D::Line3DInfo>  DebugDraw3D::line3DInfo;
std::vector<DebugDraw3D::CapsuleInfo> DebugDraw3D::capsuleInfo;
std::vector<DebugDraw3D::OBBInfo>	  DebugDraw3D::obbInfo;

void DebugDraw3D::Clear()
{
	line3DInfo.clear();
	sphereInfo.clear();
	capsuleInfo.clear();
	obbInfo.clear();
}

void DebugDraw3D::Draw3D()
{
	for (const auto& item : line3DInfo)
	{
		DxLib::DrawLine3D(
			item.start,
			item.end,
			item.color
		);
	}

	for (const auto& item : sphereInfo)
	{
		DxLib::DrawSphere3D(
			item.center,
			item.radius,
			6,
			item.color,
			item.color,
			false
		);
	}

	for (const auto& item : capsuleInfo)
	{
		DxLib::DrawCapsule3D(
			item.start,
			item.end,
			item.radius,
			6,
			item.color,
			item.color,
			false
		);
	}

	for (const auto& item : obbInfo)
	{
		//std::array<VECTOR, 8> corners = CalculateCorners(item.center, item.extents, item.rotation);

		// エッジを描画
		//for (int i = 0; i < 4; ++i) {
		//	DrawLine3D(corners[i], corners[(i + 1) % 4], GetColor(255, 0, 0)); // 上面のエッジ
		//	DrawLine3D(corners[i + 4], corners[(i + 1) % 4 + 4], GetColor(255, 0, 0)); // 下面のエッジ
		//	DrawLine3D(corners[i], corners[i + 4], GetColor(255, 0, 0)); // 上面と下面のエッジ
		//}

	}
}

void DebugDraw3D::DrawLine3D(const VECTOR& _start, const VECTOR& _end, int _color)
{
	Line3DInfo newInfo;
	newInfo.start = _start;
	newInfo.end = _end;
	newInfo.color = _color;
	line3DInfo.emplace_back(newInfo);
}

void DebugDraw3D::DrawSphere(const VECTOR& _center, float _radius, int _color, float _alpha, bool _isWire)
{
	SphereInfo newInfo;
	newInfo.center = _center;
	newInfo.radius = _radius;
	newInfo.color = _color;
	newInfo.alpha = _alpha;
	newInfo.isWire = _isWire;
	sphereInfo.emplace_back(newInfo);
}

void DebugDraw3D::DrawCapsule(const VECTOR& _center, const VECTOR& _start, const VECTOR& _end, const float _size, float _radius, int _color, float _alpha, bool _isWire)
{
	CapsuleInfo newInfo;
	newInfo.center = _center;
	newInfo.size = _size;
	newInfo.start = VAdd(_center, VGet(0.0f, _size, 0.0f));
	newInfo.end = VSub(_center, VGet(0.0f, _size, 0.0f));
	newInfo.radius = _radius;
	newInfo.color = _color;
	newInfo.alpha = _alpha;
	newInfo.isWire = _isWire;
	capsuleInfo.emplace_back(newInfo);

}

void DebugDraw3D::DrawOBB(const VECTOR& _center, const VECTOR& _extents, const MATRIX& _rotation, int _color, float _alpha, bool _isWire)
{
	OBBInfo newInfo;
	newInfo.center = _center;
	newInfo.extents = _extents;
	newInfo.rotation = _rotation;
	newInfo.color = _color;
	newInfo.alpha = _alpha;
	newInfo.isWire = _isWire;
	obbInfo.emplace_back(newInfo);
}



void DebugDraw3D::DrawBox3DLine(VECTOR minPos, VECTOR maxPos, unsigned int color)
{
	// 底面の4点
	VECTOR p1 = VGet(minPos.x, minPos.y, minPos.z);
	VECTOR p2 = VGet(maxPos.x, minPos.y, minPos.z);
	VECTOR p3 = VGet(maxPos.x, minPos.y, maxPos.z);
	VECTOR p4 = VGet(minPos.x, minPos.y, maxPos.z);

	// 上面の4点
	VECTOR p5 = VGet(minPos.x, maxPos.y, minPos.z);
	VECTOR p6 = VGet(maxPos.x, maxPos.y, minPos.z);
	VECTOR p7 = VGet(maxPos.x, maxPos.y, maxPos.z);
	VECTOR p8 = VGet(minPos.x, maxPos.y, maxPos.z);

	// 下側の四角形
	DrawLine3D(p1, p2, color);
	DrawLine3D(p2, p3, color);
	DrawLine3D(p3, p4, color);
	DrawLine3D(p4, p1, color);

	// 上側の四角形
	DrawLine3D(p5, p6, color);
	DrawLine3D(p6, p7, color);
	DrawLine3D(p7, p8, color);
	DrawLine3D(p8, p5, color);

	// 縦のライン
	DrawLine3D(p1, p5, color);
	DrawLine3D(p2, p6, color);
	DrawLine3D(p3, p7, color);
	DrawLine3D(p4, p8, color);
}



std::array<VECTOR, 8> DebugDraw3D::CalculateCorners(const VECTOR& _center, const VECTOR& _extents, const MATRIX& _rotation) const
{
	std::array<VECTOR, 8> corners;

	for (int i = 0; i < 8; ++i) {
		float x = (i & 1) ?_extents.x : -_extents.x;
		float y = (i & 2) ? _extents.y : -_extents.y;
		float z = (i & 4) ? _extents.z : -_extents.z;

		VECTOR corner = VGet(x, y, z);
		corner = VTransform(corner, _rotation);  // 回転を適用
		corners[i] = VAdd(corner, _center);       // 中心を加算
	}

	return corners;
}
