#pragma once
#include "../Base/WeaponBase.h"

class TSSword : public WeaponBase
{
private:
	std::shared_ptr<ComponentTransform> m_transform;
	std::shared_ptr<ComponentModel> m_model;
	const char* m_tag;
	int m_attachCharacterModel;
	VECTOR m_attachCharacterRightHandPos;
	float m_attachCharacterAngle;
	

	float m_playerAngle;
public:
	TSSword();
	~TSSword() override;

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

	//======================================================================
	// セッターゲッター
	//======================================================================

	void SetAttachCharacterRightHandPos(const VECTOR& _pos) { m_attachCharacterRightHandPos = _pos; }

	void SetPlayerAngle(const float& _playeerAngle) { m_playerAngle = _playeerAngle; }
	float GetPlaherangle() const { m_playerAngle; }

	void SetTag(const char* _tag) { m_tag = _tag; }
	const char* GetTag() const { return m_tag; }

	int GetModelHandle() { return m_model->modelHandle; }

	void SetPosition(const VECTOR& _pos) { m_transform->position = _pos; }
	VECTOR GetPosition() const { return m_transform->position; }

	void SetAngle(const float& _angle) { m_transform->angle = _angle; }
	float GetAngle() const { return m_transform->angle; }

	void SetAttachCharacterModel(const int& _attachCharacterModel) { m_attachCharacterModel = _attachCharacterModel; }
	int GetAttachCharacterModel() const { return m_attachCharacterModel; }

	void SetAttachCharacterAngle(const float& _angle) { m_attachCharacterAngle = _angle; }
	float GetAttachCharacerAngle() const { return m_attachCharacterAngle; }

};
