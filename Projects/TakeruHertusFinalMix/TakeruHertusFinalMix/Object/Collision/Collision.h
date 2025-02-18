#pragma once
#include "../Entity/Entity.h"

#include "../Component/ComponentTransform/ComponentTransform.h"
#include "../Component/ComponentModel/ComponentModel.h"
#include "../Component/ComponentCollisionSphere/ComponentCollisionSphere.h"
#include "../Component/ComponentCollisionPolygon/ComponentCollisionPolygon.h"

class Collision : public Entity
{
private:
	//クランプ
	template <typename T>
	T Clamp(T _value, T _minVal, T _maxVal)
	{
		if (_value < _minVal) return _minVal;
		if (_value > _maxVal) return _maxVal;
		return _value;
	}

	//最近点を求める
	void ClosestPointsOnSegments(VECTOR A1, VECTOR A2, VECTOR B1, VECTOR B2, VECTOR& closestA, VECTOR& closestB);

public:
	/*当たり判定*/
	
	/*球体と球体*/
	bool CheckSphereHitCollision(VECTOR _pos1, float _r1, VECTOR _pos2, float _r2);
	//_pos2押し出す対象
	VECTOR CheckSphereResolveCollision(VECTOR _pos1, float _r1, VECTOR _pos2, float _r2);

	/*球体とボックス*/
	bool CheckBoxHitCollision(VECTOR _spherePos, float _sphereRadius, VECTOR _boxPos, VECTOR _boxSize);

	//spherePos：位置補正対象
	VECTOR CheckBoxResolveCollision(VECTOR _spherePos, float _sphereRadius, VECTOR _boxPos, VECTOR _boxSize);

	/*カプセルとカプセル*/
	bool CapsuleCollisionCheck(VECTOR A1, VECTOR A2, float r1, VECTOR B1, VECTOR B2, float r2);

	void CapsuleResolveCollision(VECTOR& A1, VECTOR& A2, float r1, VECTOR& B1, VECTOR& B2, float r2);

	/*デバック用描画*/
	void DrawBox3D(VECTOR _boxPos, VECTOR _boxSize);

};

