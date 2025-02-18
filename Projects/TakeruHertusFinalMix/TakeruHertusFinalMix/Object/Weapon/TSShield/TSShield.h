#pragma once
#include "../Base/WeaponBase.h"

class TSShield : public WeaponBase
{
private:
	std::shared_ptr<ComponentTransform> m_transform;
	std::shared_ptr<ComponentModel> m_model;
	const char* m_tag;

public:
	TSShield();
	~TSShield() override;

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

	//======================================================================
	// セッターゲッター
	//======================================================================

	void SetTag(const char* _tag) { m_tag = _tag; }
	const char* GetTag() const { return m_tag; }

	int GetModelHandle() { return m_model->modelHandle; }

	void SetPosition(const VECTOR& _pos) { m_transform->position = _pos; }
	VECTOR GetPosition() const { return m_transform->position; }

	void SetAngle(const float& _angle) { m_transform->angle = _angle; }
	float GetAngle() const { return m_transform->angle; }


};

