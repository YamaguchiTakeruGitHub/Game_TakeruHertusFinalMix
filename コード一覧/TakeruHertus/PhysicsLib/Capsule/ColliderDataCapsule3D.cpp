#include "ColliderDataCapsule3D.h"

ColliderDataCapsule3D::ColliderDataCapsule3D()
	: ColliderData(Kind::Capsule)
	, start(VGet(0.0f, 0.0f, 0.0f))
	, end(VGet(0.0f, 0.0f, 0.0f))
	, size(0.0f)
	, radius(0.0f)
{
}
