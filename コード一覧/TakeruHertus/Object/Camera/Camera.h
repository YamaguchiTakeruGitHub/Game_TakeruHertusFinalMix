#pragma once
#include <DxLib.h>
#include <memory>
#include "../../InputDevice/InputDeviceManager.h"

class Camera
{
public:
	Camera();
	~Camera();

	void Init();
	void Update(VECTOR _target, VECTOR _LookTarget);

	void PlayerContorllCamera(VECTOR _target, VECTOR _LookTarget);

	void LookOnCamera(VECTOR _target, VECTOR _LookTarget);

	void SetPosition(const VECTOR& _position) { this->m_position = _position; }
	VECTOR GetPosition() const { return  this->m_position; }

	void SetHAngle(const float& _HAngle) { this->m_horizontalAngle = _HAngle; }
	float GetHAngle() const { return this->m_horizontalAngle; }

	void SetVAngle(const float& _VAngle) { this->m_verticalAngle = _VAngle; }
	float GetVAngle() const { return this->m_verticalAngle; }

	void SetSinParam(const float& _SinParam) { this->m_sinParam = _SinParam; }
	float GetSinParam() const { return this->m_sinParam; }

	void SetCosParam(const float& _CosParam) { this->m_cosParam = _CosParam; }
	float GetCosParam() const { return this->m_cosParam; }

private:
	VECTOR m_position;
	VECTOR m_LookAt;
	VECTOR m_previous;

	VECTOR tempPosition1;
	VECTOR tempPosition2;

	VECTOR targetPositon;



	float m_angle;
	float m_horizontalAngle;
	float m_verticalAngle;

	float m_Distance;

	float m_cosParam;
	float m_sinParam;

	float lerpFactor;

	float m_speed;

	std::shared_ptr<InputDeviceManager> m_Idm;

};

