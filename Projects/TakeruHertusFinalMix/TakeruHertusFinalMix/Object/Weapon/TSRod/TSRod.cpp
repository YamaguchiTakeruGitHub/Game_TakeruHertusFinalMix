#include "TSRod.h"

TSRod::TSRod()
{
	AddComponent<ComponentTransform>();
	m_transform = GetComponent<ComponentTransform>();

	AddComponent<ComponentModel>();
	m_model = GetComponent<ComponentModel>();
}

TSRod::~TSRod()
{
}

void TSRod::Init()
{
	Entity::InitComponents();
	m_transform->position = VGet(0, 0, 0);
	m_transform->scale = VGet(0.7, 0.7, 0.7);
	m_transform->rotation = VGet(0, 0, 0);
	m_transform->angle = 0.0f;
	m_model->LoadModel("../Asset/3D/Wepon/Rod/Section2Rod/TSRod.mv1");

}

void TSRod::Update()
{
	Entity::UpdateComponents();

	if (m_tag == "nonSelectRod")
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

	if (m_tag == "nowSelectRod")
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

void TSRod::Draw()
{
	Entity::DrawComponents();

}

void TSRod::Final()
{
	Entity::FinalComponents();

}
