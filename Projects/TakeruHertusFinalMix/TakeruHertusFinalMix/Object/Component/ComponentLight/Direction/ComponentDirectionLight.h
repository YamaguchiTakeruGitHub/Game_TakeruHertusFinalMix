#pragma once
#include "../../Base/Component.h"

class ComponentDirectionLight : public Component
{
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

	int lightHandle;

};

