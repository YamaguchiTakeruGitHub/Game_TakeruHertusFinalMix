#pragma once
#include "../Base/Component.h"
#include "../ComponentRightBody/ComponentRightBody.h"
#include "../ComponentTransform/ComponentTransform.h"
#include "../../../InputDevice/InputDeviceManager.h"

namespace MOVEMENT
{
	static constexpr float AVOIDANCETIME = 45.0f;		// 回避時間
	static constexpr float AVOIDANCESPEED = 3.0f;		// 回避スピード
	static constexpr float JUMP_POWER = 100.0f;			//ジャンプ力
	static constexpr int COMBOTIME = 45.0f;
	static constexpr float ANGLE_ROTATION_SPEED = 0.15f; //振り向き速度
}


/// <summary>
/// 引数指定：m_transform, m_rightbody
/// </summary>
class ComponentMovement : public Component
{
private:
	std::shared_ptr<InputDeviceManager> m_Idm;
	std::shared_ptr<ComponentTransform> m_transform;
	std::shared_ptr<ComponentRightBody> m_rightbody;

	//速度
	float m_speed;
	float m_WalkSpeed;

	/*フラグ*/
	bool m_isMove;		//動いているかどうか
	bool m_isWalk;		//歩き中か
	bool m_isRun;		//走り中か
	bool m_isAvoidance;	//回避
	bool m_isJump;		//ジャンプ中か
	bool m_isRaaka;		//落下中か
	bool m_isGround;

	/*カメラとの連携用*/
	float m_ConversionCameraHAngle;
	float m_ConversionCosParam;
	float m_ConversionSinParam;

	/*アングル関係*/
	float m_targetAngle;
	float m_saAngle;

	/*回避*/
	float m_aboidanceTime;
	float m_aboidanceSpeed;
	void UpdateAvoidance();

	/*ジャンプ*/
	void UpdateJump();
	float m_jumpPower;
	float m_jumpTime;
	float m_distortion;
	float m_maxJumpHeight;
	float m_midlJumpHeight;
	float m_minJumpHeight;
	bool m_isCharging;

	/*新ジャンプ*/
	float jumpHoldTime;
	float jumpVelocity;
	bool isCharginJump;


	/*攻撃中かどうかまたコンボ中かどうか*/
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
	//セッターとゲッター
	/*===============================================================*/
	/*座標のデータ*/
	void SetPosition(const VECTOR& _pos) { m_transform->position = _pos; }
	VECTOR GetPosition() const { return m_transform->position; }

	/*向きのデータ*/
	void SetDirection(const VECTOR& _direction) { m_rightbody->direction = _direction; }
	VECTOR GetDirection() const { return m_rightbody->direction; }

	/*方向と量のデータ*/
	void SetVelocity(const VECTOR& _velocity) { m_rightbody->velocity = _velocity; }
	VECTOR GetVelocity() const { return m_rightbody->velocity; }

	/*速度のデータ*/
	void SetSpeed(const float& _speed) { m_speed = _speed; }
	float GetSpeed() const { return m_speed; }

	/*動いているかのフラグ*/
	void SetIsMove(const bool& _isMove) { m_isMove = _isMove; }
	bool GetIsMove() const { return m_isMove; }

	/*カメラ変換水平アングル*/
	void SetConversionHAngle(const float& _hAngle) { m_ConversionCameraHAngle = _hAngle; }
	float GetConversionHAngle() const { return m_ConversionCameraHAngle; }

	/*カメラ変換Sinパラメータ*/
	void SetConversionSinParam(const float& _sinParam) { m_ConversionSinParam = _sinParam; }
	float GetConversionSinParam() const { return m_ConversionSinParam; }

	/*カメラ変換Cosパラメータ*/
	void SetConversionCosParam(const float& _cosParam) { m_ConversionCosParam = _cosParam; }
	float GetConversionCosParam() const { return m_ConversionCosParam; }

	/*モデルの向き*/
	void SetAngle(const float& _angle) { m_transform->angle = _angle; }
	float GetAngle() const { return m_transform->angle; }

	/*回避中のフラグ*/
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

//MEMO（2025.1.15Home）：物理処理の組み込みを開始する。