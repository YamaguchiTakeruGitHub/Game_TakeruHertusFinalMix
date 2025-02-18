#pragma once
#include "../Base/Component.h"
#include "../ComponentTransform/ComponentTransform.h"

namespace EVENTCAMERA
{
	constexpr float CAMERA_ANGLE_SPEED = 0.8f;		// ���񑬓x
	constexpr float CAMERA_PLAYER_TARGET_HEIGHT = 100.0f;	// �v���C���[���W����ǂꂾ�������ʒu�𒍎��_�Ƃ��邩
	constexpr float CAMERA_PLAYER_DISTANCE = 300.0f;		// �v���C���[�Ƃ̋���
}

class ComponentEventCamera : public Component
{
private:
	std::shared_ptr<ComponentTransform> m_transform;

	float m_speed;
	float m_Distance;

	VECTOR m_target;

	float  m_sinParam;
	float  m_cosParam;
	float  m_horizontalAngle;
	float  m_verticalAngle;

	/*�Z�N�V�����p*/
	int m_section_2Time;


	//�Z�N�V�����S
	int m_section_4Time_1;

public:
	ComponentEventCamera(std::shared_ptr<ComponentTransform> _transform);

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

	void Section_1UpdateCamera();
	void Section_2UpdateCamera();
	void Section_2UpdateLeftSelectWeponCamera();
	void Section_2UpdateRightSelectWeponCamera();
	void Section_2UpdateFowerdSelectWeponCamera();

	void Section_3UpdateEventCamera_1();
	void Section_3UpdateEventCamera_2();
	void Section_3UpdateEventCamera_3();

	void Section_4EventCamera_1();
	void Section_4EventCamera_2();



	/*===============================================================*/
	//�Z�b�^�[�ƃQ�b�^�[
	/*===============================================================*/

	/*���W�̃f�[�^*/
	void SetPosition(const VECTOR& _pos) { m_transform->position = _pos; }
	VECTOR GetPosition() const { return m_transform->position; }

	/*���x�̃f�[�^*/
	void SetSpeed(const float& _speed) { m_speed = _speed; }
	float GetSpeed() const { return m_speed; }

	/*�����_�܂ł̋����̃f�[�^*/
	void SetDistance(const float& _distance) { m_Distance = _distance; }
	float GetDistance() const { return m_Distance; }

	/*�����_�̃f�[�^*/
	void SetTarget(const VECTOR& _target) { m_target = _target; }
	VECTOR GetTarget() const { return m_target; }

	/*Sin�p�����[�^�̃f�[�^*/
	void SetSinParam(const float& _sinParam) { m_sinParam = _sinParam; }
	float GetSinParam() const { return m_sinParam; }

	/*Cos�p�����[�^�̃f�[�^*/
	void SetCosParam(const float& _cosParam) { m_cosParam = _cosParam; }
	float GetCosParam() const { return m_cosParam; }

	/*�����A���O���̃f�[�^*/
	void SetHAngle(const float& _hAngle) { m_horizontalAngle = _hAngle; }
	float GetHAngle() const { return m_horizontalAngle; }

	/*�����A���O���̃f�[�^*/
	void SetVAngle(const float& _vAngle) { m_verticalAngle = _vAngle; }
	float GetVAngle() const { return m_verticalAngle; }
};

