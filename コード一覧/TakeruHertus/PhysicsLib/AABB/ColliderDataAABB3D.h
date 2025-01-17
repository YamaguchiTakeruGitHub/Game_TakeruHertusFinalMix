#pragma once
#include "../ColliderData.h"
class ColliderDataAABB3D : public ColliderData
{
public:
	ColliderDataAABB3D();

	VECTOR m_max;
	VECTOR m_min;

};

