#pragma once
#include "../../Base/Component.h"
class ComponentAIWandering : public Component
{
private:
public:
	void Init()override;
	void Update()override;
	void Draw()override;
	void Final()override;

	void HandleInput(const std::string& _input);
};

