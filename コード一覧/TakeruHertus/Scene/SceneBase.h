#pragma once
#include "SceneType.h"
#include "../InputDevice/InputDeviceManager.h"
#include <memory>

class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase() {};
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Final() = 0;
	virtual void DebugDraw() = 0;

protected:
	std::shared_ptr<InputDeviceManager> m_Idm;
};

