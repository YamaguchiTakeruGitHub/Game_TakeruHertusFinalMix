#include "ComponentControlCamera.h"

ComponentControlCamera::ComponentControlCamera(std::shared_ptr<ComponentTransform> _transform)
	: m_transform(_transform)
	, m_horizontalAngle(0.0f)
	, m_verticalAngle(0.0f)
	, m_Distance(0.0f)
	, m_cosParam(0.0f)
	, m_sinParam(0.0f)
	, m_speed(0.0f)
	, m_target(VGet(0,0,0))
{
	m_Idm = std::make_shared<InputDeviceManager>();
}

void ComponentControlCamera::Init()
{
	m_Idm->Init();
	m_transform->position = VGet(0.0f, 50.0f, 50.0f);
	m_target = VGet(0, 0, 0);
	
	m_horizontalAngle = 0.0f;
	m_verticalAngle = 0.0f;
	m_Distance = CONTROLCAMERAPARAMETER::CAMERA_PLAYER_DISTANCE;

	m_cosParam = std::cos(m_horizontalAngle / 180.0f * DX_PI_F);
	m_sinParam = std::sin(m_horizontalAngle / 180.0f * DX_PI_F);

	m_speed = CONTROLCAMERAPARAMETER::CAMERA_ANGLE_SPEED;

	m_target.y = CONTROLCAMERAPARAMETER::CAMERA_PLAYER_TARGET_HEIGHT;
}

void ComponentControlCamera::Update()
{
	m_Idm->Update();

	auto rightStickX = m_Idm->joyPad->GetRightStickX();
	auto rightStickY = m_Idm->joyPad->GetRightStickY();

	bool Left = rightStickX != 0 && rightStickX <= 0.030519f && rightStickX >= 0.0f;
	bool Right = rightStickX != 0 && rightStickX >= -0.030519f && rightStickX <= 0.0f;
	bool Up = rightStickY != 0 && rightStickY <= 0.030519f && rightStickY >= 0.0f;
	bool Down = rightStickY != 0 && rightStickY >= -0.030519 && rightStickY <= 0.0f;


	if (rightStickX != 0 && rightStickX >= -0.030519f && rightStickX <= 0.0f)
	{
		m_horizontalAngle += m_speed;
		if (m_horizontalAngle >= 180.0f) m_horizontalAngle -= 360.0f;
	}
	if (rightStickX != 0 && rightStickX <= 0.030519f && rightStickX >= 0.0f)
	{
		m_horizontalAngle -= m_speed;
		if (m_horizontalAngle <= -180.0f) m_horizontalAngle += 360.0f;
	}
	if (rightStickY != 0 && rightStickY <= 0.030519f && rightStickY >= 0.0f)
	{
		m_verticalAngle += m_speed;
		if (m_verticalAngle >= 70.0f) m_verticalAngle = 70.0f;
	}
	if (rightStickY != 0 && rightStickY >= -0.030519f && rightStickY <= 0.0f)
	{
		m_verticalAngle -= m_speed;
		if (m_verticalAngle <= -20.0f) m_verticalAngle = -20.0f;
	}

	m_target.y = CONTROLCAMERAPARAMETER::CAMERA_PLAYER_TARGET_HEIGHT;
	//垂直方向のアングルを変換
	m_sinParam = sin(m_verticalAngle / 180.0f * DX_PI_F);
	m_cosParam = cos(m_verticalAngle / 180.0f * DX_PI_F);
	
	VECTOR tempPosition1, tempPosition2;
	tempPosition1.x = 0.0f;
	tempPosition1.y = m_sinParam * m_Distance;
	tempPosition1.z = -m_cosParam * m_Distance;

	//垂直方向のアングルを変換
	m_sinParam = sin(m_horizontalAngle / 180.0f * DX_PI_F);
	m_cosParam = cos(m_horizontalAngle / 180.0f * DX_PI_F);
	tempPosition2.x = m_cosParam * tempPosition1.x - m_sinParam * tempPosition1.z;
	tempPosition2.y = tempPosition1.y;
	tempPosition2.z = m_sinParam * tempPosition1.x + m_cosParam * tempPosition1.z;

	m_transform->position = VAdd(tempPosition2, m_target);

}

void ComponentControlCamera::Draw()
{
}

void ComponentControlCamera::Final()
{
}
