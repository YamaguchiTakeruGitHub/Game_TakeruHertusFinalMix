#pragma once
#include "../ColliderData.h"

/// <summary>
/// 当たり判定データ：3Dカプセル
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

