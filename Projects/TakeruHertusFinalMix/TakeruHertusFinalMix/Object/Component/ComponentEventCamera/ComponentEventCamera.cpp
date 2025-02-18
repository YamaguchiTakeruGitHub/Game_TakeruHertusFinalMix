#include "ComponentEventCamera.h"

ComponentEventCamera::ComponentEventCamera(std::shared_ptr<ComponentTransform> _transform)
	: m_transform(_transform)
	, m_horizontalAngle(0.0f)
	, m_verticalAngle(0.0f)
	, m_Distance(0.0f)
	, m_cosParam(0.0f)
	, m_sinParam(0.0f)
	, m_speed(0.0f)
	, m_target(VGet(0, 0, 0))
	, m_section_2Time(0)
	, m_section_4Time_1(0)
{
}

void ComponentEventCamera::Init()
{
	m_transform->position = VGet(0.0f, 700.0f, -200.0f);
	m_target = VGet(0, 0, 0);

	m_horizontalAngle = 0.0f;
	m_verticalAngle = 0.0f;
	m_Distance = 0.0f;

	m_cosParam = std::cos(m_horizontalAngle / 180.0f * DX_PI_F);
	m_sinParam = std::sin(m_horizontalAngle / 180.0f * DX_PI_F);

	m_speed = 0.0f;

	m_section_2Time = 0.0f;

	m_section_4Time_1 = 0.0f;
}

void ComponentEventCamera::Update()
{
	
}

void ComponentEventCamera::Draw()
{
}

void ComponentEventCamera::Final()
{
}

void ComponentEventCamera::Section_1UpdateCamera()
{
	if (m_transform->position.x >= 500.0f)
	{
	}
	m_transform->position.x++;
}

void ComponentEventCamera::Section_2UpdateCamera()
{
	if (m_section_2Time <= 120)//0”Ô–Ú¶
	{
		m_transform->position.z++;
		m_transform->position.y = 200.0f;
	}
	if (m_section_2Time >= 120 && m_section_2Time <= 240)//1”Ô–Ú³–Ê
	{
		m_transform->position.x++;
		m_transform->position.y = 200.0f;

	}
	if (m_section_2Time >= 240 && m_section_2Time <= 360)//‚Q”Ô–Ú‰E
	{
		m_transform->position.z--;
		m_transform->position.y = 200.0f;

	}
}

void ComponentEventCamera::Section_2UpdateLeftSelectWeponCamera()
{
	m_transform->position.x = -800.0f;
	m_transform->position.y = 150.0f;
	m_transform->position.z = 800.0f;
}

void ComponentEventCamera::Section_2UpdateRightSelectWeponCamera()
{
	m_transform->position.x = 800.0f;
	m_transform->position.y = 150.0f;
	m_transform->position.z = 800.0f;
}

void ComponentEventCamera::Section_2UpdateFowerdSelectWeponCamera()
{
	m_transform->position.x = 0.0f;
	m_transform->position.y = 150.0f;
	m_transform->position.z = 1500.0f;
}

void ComponentEventCamera::Section_3UpdateEventCamera_1()
{
	m_transform->position.z--;
	m_transform->position.y+= 0.5f;
}

void ComponentEventCamera::Section_3UpdateEventCamera_2()
{
	m_transform->position.z--;
	m_transform->position.y += 0.5f;
}

void ComponentEventCamera::Section_3UpdateEventCamera_3()
{
	m_transform->position.y += 0.5f;
}

void ComponentEventCamera::Section_4EventCamera_1()
{
	if (m_section_4Time_1 >= 800)
	{
		m_section_4Time_1 = 800;
	}
	else
	{
		m_section_4Time_1++;
	}
	if (m_section_4Time_1 <= 800)
	{
		m_transform->position.z++;
		m_transform->position.y += 0.5f;
	}

}

void ComponentEventCamera::Section_4EventCamera_2()
{
}
