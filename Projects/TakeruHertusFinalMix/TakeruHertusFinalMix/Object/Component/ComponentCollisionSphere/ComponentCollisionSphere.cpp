#include "ComponentCollisionSphere.h"

ComponentCollisionSphere::ComponentCollisionSphere(std::shared_ptr<ComponentTransform> _transform)
	: m_transform	(_transform)
{
}

void ComponentCollisionSphere::Init()
{
}

void ComponentCollisionSphere::Update()
{
}

void ComponentCollisionSphere::Draw()
{

#ifdef _DEBUG//デバック表示
	DrawSphere3D(m_transform->position, radius, 5, 0xff0000, 0xff0000, false);
	DrawSphere3D(m_transform->position, radius, 5, 0xff0000, 0xff0000, false);
#else		//リリース表示
#endif // _DEBUG


}

void ComponentCollisionSphere::Final()
{
}
