#include "Collidable.h"

Collidable::Collidable(Priority _prioriy, GameObjectTag _tag, ColliderData::Kind _colliderKind)
	: m_priority(_prioriy)
	, m_tag(_tag)
	, m_colliderData(nullptr)
	, m_nextPos(VGet(0,0,0))
{
	CreateColliderData(_colliderKind);
}

Collidable::~Collidable()
{
	//����m_colliderData�̃|�C���^��NULL�łȂ��ꍇ�A�m���ɉ����NULL�����Ă��
	if (m_colliderData != nullptr) m_colliderData.reset();
}

void Collidable::Init(std::shared_ptr<Physics> _physics)
{
	_physics->Entry(std::shared_ptr<Collidable>(this));
}

void Collidable::Final(std::shared_ptr<Physics> _physics)
{
	_physics->Exit(std::shared_ptr<Collidable>(this));
}

std::shared_ptr<ColliderData> Collidable::CreateColliderData(ColliderData::Kind _kind)
{
	if (m_colliderData != nullptr)
	{
		assert(0 && "colliderData�͊��ɍ쐬�ς݂ł��B");
		return m_colliderData;
	}

	switch (_kind)
	{
	case ColliderData::Kind::Sphere:
		m_colliderData = std::make_shared<ColliderDataSphere3D>();
		break;
	case ColliderData::Kind::Capsule:
		m_colliderData = std::make_shared<ColliderDataCapsule3D>();
		break;
	case ColliderData::Kind::AABB:
		m_colliderData = std::make_shared<ColliderDataAABB3D>();
		break;
	case ColliderData::Kind::OBB:
		m_colliderData = std::make_shared<ColliderDataOBB3D>();
		break;
	}
	return m_colliderData;
}
