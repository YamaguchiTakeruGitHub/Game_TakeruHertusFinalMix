#include "TSShield.h"

TSShield::TSShield()
{
	AddComponent<ComponentTransform>();
	m_transform = GetComponent<ComponentTransform>();

	AddComponent<ComponentModel>();
	m_model = GetComponent<ComponentModel>();
}

TSShield::~TSShield()
{
}

void TSShield::Init()
{
	Entity::InitComponents();
	m_transform->position = VGet(0, 0, 0);
	m_transform->scale = VGet(0.4, 0.4, 0.4);
	m_transform->rotation = VGet(0, 0, 0);
	m_transform->angle = 0.0f;
	m_model->LoadModel("../Asset/3D/Wepon/Seeld/Section2Seeld/TSshield.mv1");

}

void TSShield::Update()
{
Entity::UpdateComponents();

if (m_tag == "nonSelectShield")
{
	if (m_transform->angle >= 360)
	{
		m_transform->angle = 0;
	}
	else
	{
		m_transform->angle++;
	}
}

if (m_tag == "nowSelectShield")
{
	if (m_transform->angle >= 360)
	{
		m_transform->angle = 0;
	}
	else
	{
		m_transform->angle += 10.0f;
	}
}


MV1SetPosition(m_model->modelHandle, m_transform->position);
MV1SetScale(m_model->modelHandle, m_transform->scale);
MV1SetRotationXYZ(m_model->modelHandle, VGet(0, m_transform->angle * DX_PI_F / 180.0f, 0));

}

void TSShield::Draw()
{
	Entity::DrawComponents();

}

void TSShield::Final()
{
	Entity::FinalComponents();

}
