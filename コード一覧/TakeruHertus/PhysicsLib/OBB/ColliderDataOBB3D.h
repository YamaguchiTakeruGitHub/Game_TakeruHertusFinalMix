#pragma once
#include "../ColliderData.h"
#include <array>

/// <summary>
/// 当たり判定データ：3D箱
/// </summary>
class ColliderDataOBB3D : public ColliderData
{
public:
	ColliderDataOBB3D();

	VECTOR extents;//頂点の位置
	MATRIX rotation;
};

