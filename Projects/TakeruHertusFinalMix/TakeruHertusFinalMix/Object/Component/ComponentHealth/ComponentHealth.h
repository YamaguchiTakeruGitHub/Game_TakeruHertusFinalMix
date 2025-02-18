#pragma once
#include "../Base/Component.h"

class ComponentHealth : public Component
{
public:
	int health;

	void Init() override {}
	void Update() override {}
	void Draw() override {}
	void Final() override {}
};

