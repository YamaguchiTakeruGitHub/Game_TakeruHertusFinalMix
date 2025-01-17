#pragma once
#include <DxLib.h>
#include <string> 
#include "../../../AI/Path/Path.h"
#include "../../../PhysicsLib/PhysicsLib.h"
#include "../../../AnimationLib/AnimationLib.h"
#include "../../../EffectLib/EffectLib.h"


#include "../../../AnimationLib/AnimationLib.h"

class EnemySmallFish : public Collidable
{
public:	
	EnemySmallFish();
	~EnemySmallFish();

	void Init(std::shared_ptr<Physics> _physics);
	void Final(std::shared_ptr<Physics> _physics);
	void Update(std::shared_ptr<Physics> _physics);
	void Draw(std::shared_ptr<Physics> _physics);

	void OnCollide(const std::shared_ptr<Collidable>& _colider);

	void SetPosition(const VECTOR& _position) { m_righdbody.SetPosition(_position); }
	VECTOR GetPosition() const { return m_righdbody.GetPosition(); }

	void SetRadius(const float& _radius) { }

	void SetPath(std::shared_ptr<Path> _path);


	void SetHelth(const int& _helth) { this->helth = _helth; }
	int GetHelth() const { return  this->helth; }


	void HitTarget(VECTOR _center, float _r);

private:

	void State();
	void State_Idle();
	void State_Walk();
	void State_Attack();



	struct State
	{
		int currentState;
		bool isIdle;
		bool isWalk;
		bool isAttack;

	}state;

	typedef enum
	{
		eState_Idle,
		eState_Walk,
		eState_Attack,

		eState_Num

	}eState;


	std::shared_ptr<EffectLib> m_effect;
	int count;
	bool isSpawn;
	void Spawn();



	void AutoMove();
	std::shared_ptr<Path> m_path;
	int currentNodeIndex;
	VECTOR nextNode;



	int m_modelHandle;
	VECTOR scale;
	int helth;
	int tempScreen;



	bool UpdateAnim(int _modelHandle, int _attachNo, float _startTime);

	void ChangeAnim(int _modelHandle, int _animIndex, float _animSpeed);


	std::map<std::string, int> m_animIdx;
	int m_animCurrentNo;
	int m_animPrevNo;
	float m_animBlendRate;

	int m_animNowIdx;
	int m_animPrevIdx;

	float m_animSpeed;
	bool m_animIsFinish;
	
	int animCount;


};

