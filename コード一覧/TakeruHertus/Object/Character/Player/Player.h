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
/// プレイヤークラス
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

	/*プレイヤーの更新(start)*/

	/// <summary>
	/// 移動アクションを管理する
	/// </summary>
	void Update_Action_Move(std::shared_ptr<Physics>& _physics, float& _cHAngle, float&  _cVAngle, float& _SinParam, float& _CosParam);

	/// <summary>
	/// 攻撃アクションを管理する
	/// </summary>
	void Update_Action_Attack();

	/// <summary>
	/// ローリングアクションを管理する
	/// </summary>
	void Update_Action_Roring();

	/// <summary>
	/// プレイヤーのアニメーションを管理する
	/// </summary>
	void Update_Animation();


	/*プレイヤーの更新(end)*/

	/// <summary>
	/// アングルの正規化
	/// </summary>
	/// <param name="_angle"></param>
	/// <returns></returns>
	float NormalizeAngle(float _angle);
	
	/// <summary>
	/// デバック表示
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

	/*アニメーション*/
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

	//モデルのハンドルを格納
	int m_modelHandle;

	//モデルのポジションを格納
	VECTOR m_position;
	VECTOR m_velocity;
	VECTOR m_direction;

	/// <summary>
	/// モデルのフレームポジション
	/// </summary>
	struct FramPos
	{
		VECTOR head;		//頭

		VECTOR leftHand;	//左手
		VECTOR rightHand;	//右手

		VECTOR leftElbow;	//左肘
		VECTOR rightElbow;	//右肘

		VECTOR leftShoulder;//左肩
		VECTOR rightShoulder;//右肩

		VECTOR rightfeet;	//右足
		VECTOR leftfeet;	//左足

		VECTOR rightKnees;	//右膝
		VECTOR leftKnees;	//左膝

		VECTOR crotch;		//股

	}m_frame;

	//モデルのスケール
	VECTOR m_scale;

	//半径
	float m_radius;
	
	//カプセルの一番上
	VECTOR m_start;

	//カプセルの一番下
	VECTOR m_end;


	VECTOR targetPos;

	//std::shared_ptr<CSVLib> m_csvLib;

};

