#pragma once
#include "../Base/Component.h"
#include "../ComponentRightBody/ComponentRightBody.h"
#include "../ComponentTransform/ComponentTransform.h"
#include "../../../InputDevice/InputDeviceManager.h"

namespace MOVEMENT
{
	static constexpr float AVOIDANCETIME = 45.0f;		// �������
	static constexpr float AVOIDANCESPEED = 3.0f;		// ����X�s�[�h
	static constexpr float JUMP_POWER = 100.0f;			//�W�����v��
	static constexpr int COMBOTIME = 45.0f;
	static constexpr float ANGLE_ROTATION_SPEED = 0.15f; //�U��������x
}


/// <summary>
/// �����w��Fm_transform, m_rightbody
/// </summary>
class ComponentMovement : public Component
{
private:
	std::shared_ptr<InputDeviceManager> m_Idm;
	std::shared_ptr<ComponentTransform> m_transform;
	std::shared_ptr<ComponentRightBody> m_rightbody;

	//���x
	float m_speed;
	float m_WalkSpeed;

	/*�t���O*/
	bool m_isMove;		//�����Ă��邩�ǂ���
	bool m_isWalk;		//��������
	bool m_isRun;		//���蒆��
	bool m_isAvoidance;	//���
	bool m_isJump;		//�W�����v����
	bool m_isRaaka;		//��������
	bool m_isGround;

	/*�J�����Ƃ̘A�g�p*/
	float m_ConversionCameraHAngle;
	float m_ConversionCosParam;
	float m_ConversionSinParam;

	/*�A���O���֌W*/
	float m_targetAngle;
	float m_saAngle;

	/*���*/
	float m_aboidanceTime;
	float m_aboidanceSpeed;
	void UpdateAvoidance();

	/*�W�����v*/
	void UpdateJump();
	float m_jumpPower;
	float m_jumpTime;
	float m_distortion;
	float m_maxJumpHeight;
	float m_midlJumpHeight;
	float m_minJumpHeight;
	bool m_isCharging;

	/*�V�W�����v*/
	float jumpHoldTime;
	float jumpVelocity;
	bool isCharginJump;


	/*�U�������ǂ����܂��R���{�����ǂ���*/
	bool m_isAtack;
	int m_comboCount;
	void UpdateComboMove();
	int m_comboTime;

public:
	ComponentMovement(std::shared_ptr<ComponentTransform> _transform, std::shared_ptr<ComponentRightBody> _rightbody);

	void Init();
	void Update();
	void Draw();
	void Final();


	/*===============================================================*/
	//�Z�b�^�[�ƃQ�b�^�[
	/*===============================================================*/
	/*���W�̃f�[�^*/
	void SetPosition(const VECTOR& _pos) { m_transform->position = _pos; }
	VECTOR GetPosition() const { return m_transform->position; }

	/*�����̃f�[�^*/
	void SetDirection(const VECTOR& _direction) { m_rightbody->direction = _direction; }
	VECTOR GetDirection() const { return m_rightbody->direction; }

	/*�����Ɨʂ̃f�[�^*/
	void SetVelocity(const VECTOR& _velocity) { m_rightbody->velocity = _velocity; }
	VECTOR GetVelocity() const { return m_rightbody->velocity; }

	/*���x�̃f�[�^*/
	void SetSpeed(const float& _speed) { m_speed = _speed; }
	float GetSpeed() const { return m_speed; }

	/*�����Ă��邩�̃t���O*/
	void SetIsMove(const bool& _isMove) { m_isMove = _isMove; }
	bool GetIsMove() const { return m_isMove; }

	/*�J�����ϊ������A���O��*/
	void SetConversionHAngle(const float& _hAngle) { m_ConversionCameraHAngle = _hAngle; }
	float GetConversionHAngle() const { return m_ConversionCameraHAngle; }

	/*�J�����ϊ�Sin�p�����[�^*/
	void SetConversionSinParam(const float& _sinParam) { m_ConversionSinParam = _sinParam; }
	float GetConversionSinParam() const { return m_ConversionSinParam; }

	/*�J�����ϊ�Cos�p�����[�^*/
	void SetConversionCosParam(const float& _cosParam) { m_ConversionCosParam = _cosParam; }
	float GetConversionCosParam() const { return m_ConversionCosParam; }

	/*���f���̌���*/
	void SetAngle(const float& _angle) { m_transform->angle = _angle; }
	float GetAngle() const { return m_transform->angle; }

	/*��𒆂̃t���O*/
	void SetIsAboidance(const bool& _isaboidance) { m_isAvoidance = _isaboidance; }
	bool GetISAboidance() const { return m_isAvoidance; }

	void SetIsGround(const bool& _isGround) { m_isGround = _isGround; }
	bool GetIsGround() const { return m_isGround; }

	void SetIsJump(const bool& _isJump) { m_isJump = _isJump; }
	bool GetIsJump() const { return m_isJump; }


	void SetIsAtack(const bool& _isAtack) { m_isAtack = _isAtack; }
	bool GetIsAtack() const { return m_isAtack; }

	void SetComboCount(const int& _comboCount) { m_comboCount = _comboCount; }
	int GetIsComboCount() const { return m_comboCount; }
};

//MEMO�i2025.1.15Home�j�F���������̑g�ݍ��݂��J�n����B