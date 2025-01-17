#pragma once
#include "../ColliderData.h"

/// <summary>
/// 当たり判定データ：3D球
/// </summary>
class ColliderDataSphere3D : public ColliderData
{
public:
	ColliderDataSphere3D();

	/// <summary>
	/// 球の半径
	/// </summary>
	float radius;

};

