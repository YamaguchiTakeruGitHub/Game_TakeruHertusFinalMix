#pragma once
#include "../../Entity/Entity.h"

class Character : public Entity
{
public:
	Character();
	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Final();

protected:
	

};

