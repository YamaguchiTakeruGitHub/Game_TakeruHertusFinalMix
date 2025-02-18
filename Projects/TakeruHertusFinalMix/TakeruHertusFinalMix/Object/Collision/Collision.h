#pragma once
#include "../Entity/Entity.h"

#include "../Component/ComponentTransform/ComponentTransform.h"
#include "../Component/ComponentModel/ComponentModel.h"
#include "../Component/ComponentCollisionSphere/ComponentCollisionSphere.h"
#include "../Component/ComponentCollisionPolygon/ComponentCollisionPolygon.h"

class Collision : public Entity
{
private:
	//�N�����v
	template <typename T>
	T Clamp(T _value, T _minVal, T _maxVal)
	{
		if (_value < _minVal) return _minVal;
		if (_value > _maxVal) return _maxVal;
		return _value;
	}

	//�ŋߓ_�����߂�
	void ClosestPointsOnSegments(VECTOR A1, VECTOR A2, VECTOR B1, VECTOR B2, VECTOR& closestA, VECTOR& closestB);

public:
	/*�����蔻��*/
	
	/*���̂Ƌ���*/
	bool CheckSphereHitCollision(VECTOR _pos1, float _r1, VECTOR _pos2, float _r2);
	//_pos2�����o���Ώ�
	VECTOR CheckSphereResolveCollision(VECTOR _pos1, float _r1, VECTOR _pos2, float _r2);

	/*���̂ƃ{�b�N�X*/
	bool CheckBoxHitCollision(VECTOR _spherePos, float _sphereRadius, VECTOR _boxPos, VECTOR _boxSize);

	//spherePos�F�ʒu�␳�Ώ�
	VECTOR CheckBoxResolveCollision(VECTOR _spherePos, float _sphereRadius, VECTOR _boxPos, VECTOR _boxSize);

	/*�J�v�Z���ƃJ�v�Z��*/
	bool CapsuleCollisionCheck(VECTOR A1, VECTOR A2, float r1, VECTOR B1, VECTOR B2, float r2);

	void CapsuleResolveCollision(VECTOR& A1, VECTOR& A2, float r1, VECTOR& B1, VECTOR& B2, float r2);

	/*�f�o�b�N�p�`��*/
	void DrawBox3D(VECTOR _boxPos, VECTOR _boxSize);

};

