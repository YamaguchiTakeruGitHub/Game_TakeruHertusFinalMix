#pragma once
#include "../ColliderData.h"

/// <summary>
/// �����蔻��f�[�^�F3D�J�v�Z��
/// </summary>
class ColliderDataCapsule3D : public ColliderData
{
public:
	ColliderDataCapsule3D();

	VECTOR start;
	VECTOR end;
	float size;
	float radius;
};

