#include "Enemy_Doragon.h"

Enemy_Doragon::Enemy_Doragon()
{
	AddComponent<ComponentTransform>();
	m_transform = GetComponent<ComponentTransform>();

	AddComponent<ComponentModel>();
	m_model = GetComponent<ComponentModel>();

	AddComponent<ComponentCollisionSphere>(m_transform);
	m_sphere = GetComponent<ComponentCollisionSphere>();

	AddComponent<ComponentAnimation>(m_model);
	m_animation = GetComponent<ComponentAnimation>();
}

Enemy_Doragon::~Enemy_Doragon()
{
}

void Enemy_Doragon::Init()
{
	Entity::InitComponents();
	m_transform->position = VGet(0, 100, 0);
	m_transform->scale = VGet(0.1f, 0.1f, 0.1f);
	m_sphere->radius = 50.0f;

	SetUseASyncLoadFlag(true);
	m_model->LoadModel("../Asset/3D/Enemy/Enemy_Doragon/Dragon 2.5_fbx.mv1");
	SetUseASyncLoadFlag(false);

	//ˆÚ“®‚µ‚Ä‚¢‚é‚©
	isMove = false;
}

void Enemy_Doragon::Update()
{
	Entity::UpdateComponents();


	MV1SetScale(m_model->modelHandle, m_transform->scale);
	MV1SetPosition(m_model->modelHandle, m_transform->position);
}

void Enemy_Doragon::Draw()
{
	Entity::DrawComponents();

}

void Enemy_Doragon::Final()
{
	Entity::FinalComponents();

}
