#pragma once
#include "../../Base/Component.h"

class ComponentCircleHPBar : public Component
{
private:

public:
	ComponentCircleHPBar();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;
};

