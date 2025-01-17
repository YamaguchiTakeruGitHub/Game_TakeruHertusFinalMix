#include "ColliderDataAABB3D.h"

ColliderDataAABB3D::ColliderDataAABB3D()
	: ColliderData(Kind::AABB)
	, m_min(VGet(0,0,0))
	, m_max(VGet(0,0,0))
{
}
