#include "InputDeviceManager.h"

InputDeviceManager::InputDeviceManager()
{
	joyPad = std::make_shared<JoyPad>();
}

InputDeviceManager::~InputDeviceManager()
{
}

void InputDeviceManager::Init()
{
	joyPad.get()->Init();
}

void InputDeviceManager::Update()
{
	joyPad.get()->Update();
}
