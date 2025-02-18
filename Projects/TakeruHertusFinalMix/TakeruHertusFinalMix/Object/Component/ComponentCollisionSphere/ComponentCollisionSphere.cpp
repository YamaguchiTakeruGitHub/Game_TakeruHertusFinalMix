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

#ifdef _DEBUG//�f�o�b�N�\��
	DrawSphere3D(m_transform->position, radius, 5, 0xff0000, 0xff0000, false);
	DrawSphere3D(m_transform->position, radius, 5, 0xff0000, 0xff0000, false);
#else		//�����[�X�\��
#endif // _DEBUG


}

void ComponentCollisionSphere::Final()
{
}
