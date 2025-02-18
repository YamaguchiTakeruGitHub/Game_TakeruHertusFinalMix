#pragma once
#include "../../../Entity/Entity.h"
#include "../../../../CSVLib/CsvData_Reading_And_Writing_Equipment.h"
#include "../../../Collision/Collision.h"

class Enemy_Fox : public Entity
{
private:
	enum class EnemyState
	{
		Idle,	//‘Ò‹@
		Chase,	//’ÇÕ
		Attack,	//UŒ‚
		Retreat,//“P‘Ş
		Deth,	//€–S
	};
	EnemyState state;
	std::shared_ptr<Collision> m_collision = std::make_shared<Collision>();

	std::shared_ptr<ComponentTransform> m_transform;
	std::shared_ptr<ComponentCollisionCapsule> m_capsule;
	std::shared_ptr<ComponentRightBody> m_rightbody;
	std::shared_ptr<ComponentModel> m_model;
	std::shared_ptr<ComponentAnimation> m_animation;

	bool m_isDad;
	int m_hitPoint;
	
	float m_chaseDistance;
	float m_attackDistance;
	float m_damageDistance;

	VECTOR initPosition;
	VECTOR targetPosition;

	//ŠO•”ƒtƒ@ƒCƒ‹‚Ì“Ç‚İ‚İ
	std::string filename;
	std::vector<std::vector<std::string>> Data;
	
	const char* m_tag;

public:
	Enemy_Fox();

	void Init();
	void Update(VECTOR _playerPos);
	void Draw();
	void Final();

	void TakeDamage(int _damege);

	void SetIsDad(const bool& _isDad) { m_isDad = _isDad; }
	bool GetIsDad() const { return m_isDad; }

	void UpdateAI(VECTOR _playerPos);
	void SetTag(const char* _tag) { m_tag = _tag; }

	float GetDamageDistance() const { return m_damageDistance; }


	void SetPosition(const VECTOR& _pos) { m_transform->position = _pos; }
	VECTOR GetPosition() const { return m_transform->position; }

private:
	void MoveTowards(VECTOR& _targetPos);
	void AttackPlayer();
	void SetRandomTargetAround(VECTOR& _playerPos);
};

