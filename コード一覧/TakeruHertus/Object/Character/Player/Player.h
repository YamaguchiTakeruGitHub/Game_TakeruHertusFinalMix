#pragma once
#include <DxLib.h>
#include <memory>
#include <string>
#include "../../../InputDevice/InputDeviceManager.h"
#include "../../Camera/Camera.h"
#include "../../../System/Command/Command.h"
#include "../../../EffectLib/EffectLib.h"
#include "../../../PhysicsLib/PhysicsLib.h"
#include "../../../MathLib/MathLib.h"

#include "../EnemySmallFish/EnemySmallFish.h"


//#include "../../LibCom/CSVLib/CSVLib.h"



class Collidable;
class Physics;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player : public Collidable
{
public:
	Player();
	~Player();

	//void loadData(const std::string& _filename);


	void Init(std::shared_ptr<Physics> _physics) override;
	void Update(std::shared_ptr<Physics> _physics,  float _cHAngle, float  _cVAngle, float _SinParam, float _CosParam);
	void Draw();
	void Final(std::shared_ptr<Physics> _physics);

	void OnCollide(const std::shared_ptr<Collidable>& _colider);

	void SetFrame();

	void SetPosition(const VECTOR& _position) { this->m_position = _position; }
	VECTOR GetPosition() const { return  this->m_position; }

	void SetDirection(const VECTOR& _direction) { this->m_direction = _direction; }
	VECTOR GetDirection() const { return  this->m_direction; }
	
	void SetIsAttack(const bool& _isAttack) { m_attack.isAttackNow = _isAttack; }
	bool GetIsAttack() const { return this->m_attack.isAttackNow; }



	bool HitAttackCheck(VECTOR _center, float radius);


private:

	/*�v���C���[�̍X�V(start)*/

	/// <summary>
	/// �ړ��A�N�V�������Ǘ�����
	/// </summary>
	void Update_Action_Move(std::shared_ptr<Physics>& _physics, float& _cHAngle, float&  _cVAngle, float& _SinParam, float& _CosParam);

	/// <summary>
	/// �U���A�N�V�������Ǘ�����
	/// </summary>
	void Update_Action_Attack();

	/// <summary>
	/// ���[�����O�A�N�V�������Ǘ�����
	/// </summary>
	void Update_Action_Roring();

	/// <summary>
	/// �v���C���[�̃A�j���[�V�������Ǘ�����
	/// </summary>
	void Update_Animation();


	/*�v���C���[�̍X�V(end)*/

	/// <summary>
	/// �A���O���̐��K��
	/// </summary>
	/// <param name="_angle"></param>
	/// <returns></returns>
	float NormalizeAngle(float _angle);
	
	/// <summary>
	/// �f�o�b�N�\��
	/// </summary>
	void DebugDraw();

	std::shared_ptr<InputDeviceManager> m_Idm;
	std::shared_ptr<EnemySmallFish> m_enemy1;
	std::shared_ptr<Camera> m_camera;
	std::shared_ptr<Command> m_command;
	std::shared_ptr<EffectLib> m_effectLib;
	std::shared_ptr<EffectLib> m_effectLib2;
	std::shared_ptr<EffectLib> m_effectHitAttack;


	struct Attack
	{
		bool isAttack;
		bool isAttackNow;
		int attackCount;
		int attackTime;
	}m_attack;

	struct Roring
	{
		bool isRoring;
		bool isRoringNow;
		int count;

	}m_roring;

	struct AnimationAttachIndex
	{
		int IdelIndex;
		int RunIndex;
		int WalkIndex;
		int RollingIndex;
		int Attack1Index;
		int Attack2Index;
		int Attack3Index;
		int Attack4Index;
	}m_anim_AttachIndex;

	/*�A�j���[�V����*/
	int m_Anim_MoveFrameIndex;
	int m_Anim_AttachIndex;
	float m_Anim_PlayTime;
	float m_Anim_TotalTime;
	float m_Anim_NowTime;
	bool m_IsRun;

	bool isJump;
	bool isMove;
	float speed;
	float m_angle;
	float m_newAngle;

	VECTOR tempMoveVector;

	//���f���̃n���h�����i�[
	int m_modelHandle;

	//���f���̃|�W�V�������i�[
	VECTOR m_position;
	VECTOR m_velocity;
	VECTOR m_direction;

	/// <summary>
	/// ���f���̃t���[���|�W�V����
	/// </summary>
	struct FramPos
	{
		VECTOR head;		//��

		VECTOR leftHand;	//����
		VECTOR rightHand;	//�E��

		VECTOR leftElbow;	//���I
		VECTOR rightElbow;	//�E�I

		VECTOR leftShoulder;//����
		VECTOR rightShoulder;//�E��

		VECTOR rightfeet;	//�E��
		VECTOR leftfeet;	//����

		VECTOR rightKnees;	//�E�G
		VECTOR leftKnees;	//���G

		VECTOR crotch;		//��

	}m_frame;

	//���f���̃X�P�[��
	VECTOR m_scale;

	//���a
	float m_radius;
	
	//�J�v�Z���̈�ԏ�
	VECTOR m_start;

	//�J�v�Z���̈�ԉ�
	VECTOR m_end;


	VECTOR targetPos;

	//std::shared_ptr<CSVLib> m_csvLib;

};

