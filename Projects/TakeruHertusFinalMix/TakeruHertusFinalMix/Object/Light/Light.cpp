#include "Light.h"

Light::Light()
{
	AddComponent<ComponentDirectionLight>();
	m_directionLight = GetComponent<ComponentDirectionLight>();

	AddComponent<ComponentTransform>();
	m_transform = GetComponent<ComponentTransform>();
}

void Light::Init()
{
	Entity::InitComponents();
	m_transform->position = VGet(0, 0, 0);
	SetLightEnable(true);
}

void Light::Update()
{
	Entity::UpdateComponents();

	if (m_tag == "normal")
	{
		m_transform->position = VGet(0, 300, 0);
		
		SetLightDirectionHandle(m_directionLight->lightHandle, VGet(0,-1,0));
	}

	if (m_tag == "section_2LeftWeponSelectEvent")
	{
		m_transform->position = VGet(0, 300, 0);
		SetLightDirectionHandle(m_directionLight->lightHandle, VGet(-1, -1, 0));
	}
	SetLightPositionHandle(m_directionLight->lightHandle, m_transform->position);
}

void Light::Draw()
{
	Entity::DrawComponents();
}

void Light::Final()
{
	Entity::FinalComponents();
}
