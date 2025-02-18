#pragma once
#include "../../Base/Character.h"

class EnemyBase : public Character
{
private:
public:
	EnemyBase(){}
	virtual ~EnemyBase() {}

	virtual void Init(){}
	virtual void Update() {}
	virtual void Draw() {}
	virtual void Final() {}
};

