#include "ComponentCollisionCapsule.h"

ComponentCollisionCapsule::ComponentCollisionCapsule(std::shared_ptr<ComponentTransform> _transform)
	: m_transform(_transform)
{
}

void ComponentCollisionCapsule::Init()
{
}

void ComponentCollisionCapsule::Update()
{
}

void ComponentCollisionCapsule::Draw()
{
#ifdef _DEBUG//�f�o�b�N�\��
	DrawCapsule3D(maxPosition, minPosition, radius, 5, 0x00ff00, 0x00ff00, false);
#else		//�����[�X�\��

#endif // _DEBUG

}

void ComponentCollisionCapsule::Final()
{
}
