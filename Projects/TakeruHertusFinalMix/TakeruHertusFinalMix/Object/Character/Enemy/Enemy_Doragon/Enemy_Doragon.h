#pragma once
#include "../Base/EnemyBase.h"

class Enemy_Doragon : public EnemyBase
{
private:
	std::shared_ptr<ComponentTransform> m_transform;
	std::shared_ptr<ComponentModel> m_model;
	std::shared_ptr<ComponentCollisionSphere> m_sphere;
	std::shared_ptr<ComponentAnimation> m_animation;

	float time;
	bool isMove;

public:
	Enemy_Doragon();
	~Enemy_Doragon()override;

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

	void SetIsMove(const bool& _isMove) { isMove = _isMove; }
	bool GetIsMove() const { return isMove; }

	int GetModelHandle() { return m_model->modelHandle; }
	void SetPosition(const VECTOR& _position) { m_transform->position = _position; }
	VECTOR GetPosition() const { return m_transform->position; }
	float GetRadius() const { return m_sphere->radius; }
};

