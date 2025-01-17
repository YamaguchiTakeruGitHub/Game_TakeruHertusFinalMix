#include "ColliderDataOBB3D.h"

ColliderDataOBB3D::ColliderDataOBB3D()
	: ColliderData(Kind::OBB)
	, extents(VGet(0.0f, 0.0f, 0.0f))
	, rotation()
{
}
