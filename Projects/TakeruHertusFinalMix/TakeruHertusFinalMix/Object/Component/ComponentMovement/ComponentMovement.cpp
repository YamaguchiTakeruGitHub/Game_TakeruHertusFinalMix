#include "ComponentMovement.h"
#include <cmath>
#include <iostream>

void ComponentMovement::UpdateAvoidance()
{
	//回避
	if (m_Idm->joyPad->isX == true)
	{
		m_aboidanceTime = MOVEMENT::AVOIDANCETIME;
	}

	if (m_aboidanceTime >= 0)
	{
		m_isAvoidance = true;
		m_aboidanceTime--;
	}
	else
	{
		m_isAvoidance = false;
	}

	//回避中
	if (m_isAvoidance == true)
	{
		m_isMove = false;
		
		VECTOR tempMoveVector;
		tempMoveVector.x = m_rightbody->velocity.x * m_ConversionCosParam - m_rightbody->velocity.z * m_ConversionSinParam;
		tempMoveVector.y = 0.0f;
		tempMoveVector.z = m_rightbody->velocity.x * m_ConversionSinParam + m_rightbody->velocity.z * m_ConversionCosParam;

		m_transform->position = VAdd(m_transform->position, tempMoveVector);
	}
}


void ComponentMovement::UpdateJump()
{
	const float maxJumpTime = 8.0f;
	const float minJumpForce = 3.0f;
	const float maxJumpForce = 10.0f;
	const float gravity = -0.3f;
	const float deltatime = 1.0f;

	if (m_isGround == true && m_Idm->joyPad->isA == true)
	{
		jumpHoldTime = 0.0f;
		m_isJump = true;
	}

	if (m_isJump == true && m_Idm->joyPad->isAHold == true)
	{
		jumpHoldTime += deltatime;

		jumpHoldTime = min(jumpHoldTime, maxJumpTime);

	}

	if (m_isJump == true && (!m_Idm->joyPad->isAHold || jumpHoldTime >= maxJumpTime))
	{
		float jumpPower = minJumpForce + (maxJumpForce - minJumpForce) * (jumpHoldTime / maxJumpTime);
		jumpVelocity = jumpPower;
		m_isJump = false;
		m_isGround = false;
		DrawFormatString(0, 0, 0xffffff, "jumppower:%f", jumpPower);
	}

	if (!m_isGround)
	{
		jumpVelocity += gravity * deltatime;
		m_transform->position.y += jumpVelocity * deltatime;

	}

}

//void ComponentMovement::UpdateJump()
//{
//
//	m_transform->position.y -= 1.5f;
//
//
//	if (m_isJump == true)
//	{
//		if (m_jumpTime > 15.0f)
//		{
//			m_jumpTime = 15.0f;
//			m_isJump = false;
//		}
//		else
//		{
//			m_jumpTime += 0.8f;
//		}
//		m_transform->position.y += m_jumpTime;
//		
//	}
//	else
//	{
//		m_transform->position.y -= 2.8f;
//	}
//
//	
//	
//	if (m_Idm->joyPad->isA == true && m_isGround == true)
//	{
//		m_isJump = true;
//	}
//	
//	if (m_isGround == true && m_isJump == false)
//	{
//		m_jumpTime = 0.0f;
//		m_isJump = false;
//		
//	}
//
//	
//}

void ComponentMovement::UpdateComboMove()
{

	if (m_comboCount == 2)
	{
		
		VECTOR tempMoveVector;
		tempMoveVector.x = m_rightbody->velocity.x * m_ConversionCosParam - m_rightbody->velocity.z * m_ConversionSinParam;
		tempMoveVector.y = 0.0f;
		tempMoveVector.z = m_rightbody->velocity.x * m_ConversionSinParam + m_rightbody->velocity.z * m_ConversionCosParam;

		m_transform->position = VAdd(m_transform->position, tempMoveVector);

	}
	if (m_comboCount == 3)
	{
		
		VECTOR tempMoveVector;
		tempMoveVector.x = m_rightbody->velocity.x * m_ConversionCosParam - m_rightbody->velocity.z * m_ConversionSinParam;
		tempMoveVector.y = 0.0f;
		tempMoveVector.z = m_rightbody->velocity.x * m_ConversionSinParam + m_rightbody->velocity.z * m_ConversionCosParam;

		m_transform->position = VAdd(m_transform->position, tempMoveVector);
	}
	if (m_comboCount == 4)
	{
		
		VECTOR tempMoveVector;
		tempMoveVector.x = m_rightbody->velocity.x * m_ConversionCosParam - m_rightbody->velocity.z * m_ConversionSinParam;
		tempMoveVector.y = 0.0f;
		tempMoveVector.z = m_rightbody->velocity.x * m_ConversionSinParam + m_rightbody->velocity.z * m_ConversionCosParam;

		m_transform->position = VAdd(m_transform->position, tempMoveVector);
	}
}

ComponentMovement::ComponentMovement(std::shared_ptr<ComponentTransform> _transform, std::shared_ptr<ComponentRightBody> _rightbody)
	: m_transform(_transform)
	, m_rightbody(_rightbody)
	, m_speed(0.0f)
	, m_WalkSpeed(0.0f)
	, m_isMove(false)
	, m_isRun(false)
	, m_isWalk(false)
	, m_isRaaka(false)
	, m_isGround(false)

	, m_isAtack(false)
	, m_comboCount(0)
	, m_comboTime(0)

	, m_isAvoidance(false)
	, m_aboidanceSpeed(0.0f)
	, m_aboidanceTime(0.0f)
	
	, m_isJump(false)
	, m_jumpPower(0.0f)
	, m_jumpTime(0.0f)
	, m_distortion(0.0f)
	, m_maxJumpHeight(0.0f)
	, m_midlJumpHeight(0.0f)
	, m_minJumpHeight(0.0f)
	, m_isCharging(false)

	, jumpHoldTime(0.0f)
	, jumpVelocity(0.0f)
	, isCharginJump(false)

	, m_ConversionCameraHAngle(0.0f)
	, m_ConversionCosParam(0.0f)
	, m_ConversionSinParam(0.0f)
	, m_targetAngle(0.0f)
	, m_saAngle(0.0f)
{
	m_Idm = std::make_shared<InputDeviceManager>();
}

void ComponentMovement::Init()
{
	m_Idm->Init();
	m_rightbody->direction = VGet(0, 0, 0);
	m_rightbody->velocity = VGet(0, 0, 0);

	m_speed = 5.0f;
	m_WalkSpeed = 1.0f;

	m_isMove = false;
	m_isRun = false;
	m_isWalk = false;
	m_isGround = false;

	m_isAtack = false;
	m_comboCount = 0;
	m_comboTime = 0;

	m_isAvoidance = false;
	m_aboidanceSpeed = MOVEMENT::AVOIDANCESPEED;
	m_aboidanceTime = 0.0f;
	
	m_isJump = false;
	m_jumpPower = 100.0f;
	m_jumpTime = 0.0f;
	m_distortion = 3.0f;

	jumpHoldTime = 0.0f;
	jumpVelocity = 0.0f;
	isCharginJump = false;
	
	m_ConversionCameraHAngle = 0.0f;
	m_ConversionCosParam = 0.0f;
	m_ConversionSinParam = 0.0f;

	m_targetAngle = 0.0f;
	m_saAngle = 0.0f;
}

void ComponentMovement::Update()
{
	m_Idm->Update();

	

	//左スティックの召喚
	float leftStickX = m_Idm.get()->joyPad->GetLeftStickX();
	float leftStickY = m_Idm.get()->joyPad->GetLeftStickY();

	bool Left = leftStickX != 0 && leftStickX >= -0.030519f && leftStickX <= 0.0f;
	bool Right = leftStickX != 0 && leftStickX <= 0.030519f && leftStickX >= 0.0f;
	bool Up = leftStickY != 0 && leftStickY <= 0.030519f && leftStickY >= 0.0f;
	bool Down = leftStickY != 0 && leftStickY >= -0.030519 && leftStickY <= 0.0f;

	bool hLeft = leftStickX != 0 && leftStickX >= -0.0152595f && leftStickX <= 0.0f;
	bool hRight = leftStickX != 0 && leftStickX <= 0.0152595f && leftStickX >= 0.0f;
	bool hUp = leftStickY != 0 && leftStickY <= 0.0152595f && leftStickY >= 0.0f;
	bool hDown = leftStickY != 0 && leftStickY >= -0.0152595 && leftStickY <= 0.0f;

	

	m_rightbody->direction = VGet(0.0f, 0.0f, 0.0f);
	m_isMove = false;
	m_isRun = false;
	m_isWalk = false;
	
	
	if (m_isAvoidance == false && m_isAtack == false)
	{
		if (leftStickX != 0.0f || leftStickY != 0.0f)
		{
			m_isMove = true;
			m_isRun = true;

			float targetAngleRad = atan2(-leftStickX, leftStickY);//角度をラジアンで取得
			float targetangleDeg = targetAngleRad * 180.0f / DX_PI_F;

			float targetAngle = targetangleDeg - m_ConversionCameraHAngle;
			float angleDifference = targetAngle - m_transform->angle;

			if (angleDifference > 180.0f)
			{
				angleDifference -= 360.0f;
			}
			if (angleDifference < -180.0f)
			{
				angleDifference += 360.0f;
			}

			m_transform->angle += angleDifference * MOVEMENT::ANGLE_ROTATION_SPEED;

			m_rightbody->direction.x = sin(targetAngleRad);
			m_rightbody->direction.z = cos(targetAngleRad);

		}

		//もし動いているなら
		if (VSquareSize(m_rightbody->direction) > 0)
		{
			m_rightbody->direction = VNorm(m_rightbody->direction);
		}

		
		//動いているなら
		if (m_isMove == true)
		{
			if (m_isRun == true)
			{
				m_rightbody->velocity = VGet(m_rightbody->direction.x * m_speed, 0.0f, m_rightbody->direction.z * m_speed);
			}
			if (m_isWalk == true)
			{
				m_rightbody->velocity = VGet(m_rightbody->direction.x * m_WalkSpeed, 0.0f, m_rightbody->direction.z * m_WalkSpeed);
			}
			

			m_ConversionSinParam = sin(m_ConversionCameraHAngle / 180.0f * DX_PI_F);
			m_ConversionCosParam = cos(m_ConversionCameraHAngle / 180.0f * DX_PI_F);

			VECTOR tempMoveVector;
			tempMoveVector.x = m_rightbody->velocity.x * m_ConversionCosParam - m_rightbody->velocity.z * m_ConversionSinParam;
			tempMoveVector.y = 0.0f;
			tempMoveVector.z = m_rightbody->velocity.x * m_ConversionSinParam + m_rightbody->velocity.z * m_ConversionCosParam;

			m_transform->position = VAdd(m_transform->position, tempMoveVector);
		}
	}
	
	
	//回避処理
	UpdateAvoidance();
	UpdateJump();
	
}

void ComponentMovement::Draw()
{

	//DrawFormatString(0, 60, GetColor(255, 255, 255), "x:%f, y:%f, z:%f", m_transform->position.x, m_transform->position.y, m_transform->position.z);
#ifdef _DEBUG
	if (m_isGround == true)
	{
		DrawFormatString(600, 60, GetColor(255, 255, 255), "isGround == true");
	}
	else
	if (m_isGround == false)
	{
		DrawFormatString(600, 60, GetColor(255, 255, 255), "isGround == false");

	}
#endif // _DEBUG
}

void ComponentMovement::Final()
{
}
