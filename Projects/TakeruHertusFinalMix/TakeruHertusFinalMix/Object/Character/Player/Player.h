#pragma once
#include "../../Entity/Entity.h"
#include "../Base/Character.h"

#define COMBODURATION 13.0f;//コンボ持続時間

class Player : public Character//public Entity
{
private:

	//std::shared_ptr<ComponentCollisionCapsule> m_capsule;//カプセル
	std::shared_ptr<ComponentCollisionSphere> m_sphere;//球体データ
	std::shared_ptr<ComponentRightBody> m_rightBody;
	std::shared_ptr<ComponentTransform> m_transform;
	std::shared_ptr<ComponentModel> m_model;

	//行動
	std::shared_ptr<ComponentMovement> m_movement;
	//アニメーションのコンポーネント
	std::shared_ptr<ComponentAnimation> m_animation;
	//コマンド
	//std::shared_ptr<ComponentComandSystem> m_commandSystem;

	/*アニメーション*/
	void PlayerAnim();

	/*コンボ用の変数*/
	int comboCount;
	float comboTime;
	bool isCombo;

	void StartCombo();
	void UpdateCombo();
	void ResetCombo();

	void ComboUpdate();
	VECTOR rightHandPos;

	/*コマンド用フラグ*/
	bool m_isAttack;
	bool m_isMagic;
	bool m_isItem;
	bool m_isMenu;

	/*左手のインデックス*/
	static constexpr int m_rightHandIndex = 71;
	MATRIX m_rightHandMatrix;
	VECTOR m_rightHandPosition;



public:
	Player();

	void Init();
	void Update(float _cHAngle, float _sinParam, float _cosParam);
	void Draw();
	void Final();


	//======================================================================
	// セッターゲッター
	//======================================================================
	void SetDirectionY(const float& _dirY) { m_rightBody->direction.y = _dirY; }
	
	void SetAngle(const float& _angle) { m_movement->SetAngle(_angle); }
	float GetAngle() const { return m_movement->GetAngle(); }

	void SetRightHandPosition(const VECTOR& _rightHandPos) { m_rightHandPosition = _rightHandPos; }
	VECTOR GetRightHandPosition() const { return m_rightHandPosition; }

	int GetModelHandle() { return m_model->modelHandle; }

	void SetPosition(const VECTOR& _pos) { m_transform->position = _pos; }
	VECTOR GetPosition() const { return m_transform->position; }

	void SetIsGround(const bool& _isGround) { m_movement->SetIsGround(_isGround); }
	bool GetIsGround() const { return m_movement->GetIsGround(); }

	void SetIsAttackCommand(const bool& _isAttack) { m_isAttack = _isAttack; }
	bool GetIsAttackCommand() { return m_isAttack; }

	void SetIsMagic(const bool& _isMagic) { m_isMagic = _isMagic; }
	bool GetIsMagic() { return m_isMagic; }

	void SetIsItem(const bool& _isItem) { m_isItem = _isItem; }
	bool GetIsItem() { return m_isItem; }

	void SetIsMenu(const bool& _isMenu) { m_isMenu = _isMenu; }
	bool GetIsMenu() { return m_isMenu; }

	void SetIsMove(const bool& _isMove) { m_movement->SetIsMove(_isMove); }
	bool GetIsMove() { return m_movement->GetIsMove(); }

	void SetIsJump(const bool& _isJump) { m_movement->SetIsJump(_isJump); }
	bool GetIsJump() { return m_movement->GetIsJump(); }

	void SetIsAnim(const int& _animNum) { m_animation->PlayAnim(_animNum); }
	void GetAnimUpdate() { return m_animation->Update(); }

	void SetIsAttack(const bool& _isAttack) { m_movement->SetIsAtack(true); }
	bool GetIsAttack() const { return m_movement->GetIsAtack(); }

	/*球体データ*/
	float GetRadius() const { return m_sphere->radius; }

	/*カプセル*/
	/*void SetMaxPosition(const VECTOR& _maxPos) { m_capsule->maxPosition = _maxPos; }
	VECTOR GetMaxPosition() const { return m_capsule->maxPosition; }

	void SetMinPosition(const VECTOR& _minPos) { m_capsule->minPosition = _minPos; }
	VECTOR GetMinPosition() const { return m_capsule->minPosition; }
	
	void SetRadius(const float& _radius) { m_capsule->radius = _radius; }
	float GetRadius() const { return m_capsule->radius; }*/
};

