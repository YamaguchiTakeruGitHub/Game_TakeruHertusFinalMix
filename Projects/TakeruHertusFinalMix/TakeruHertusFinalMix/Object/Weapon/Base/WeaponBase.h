#pragma once
#include "../../Entity/Entity.h"

class WeaponBase : public Entity
{
private:
public:
	WeaponBase() {};
	virtual ~WeaponBase() {};

	virtual void Init() {};
	virtual void Update() {};
	virtual void Draw() {};
	virtual void Final() {};

};

