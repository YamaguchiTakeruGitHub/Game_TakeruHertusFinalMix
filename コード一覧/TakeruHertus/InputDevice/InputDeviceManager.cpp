#include "InputDeviceManager.h"

InputDeviceManager::InputDeviceManager()
{
	joyPad = new JoyPad;
}

InputDeviceManager::~InputDeviceManager()
{
	joyPad = nullptr;
	delete(joyPad);
}

void InputDeviceManager::Init()
{
	joyPad->Init();
}

void InputDeviceManager::Update()
{
	joyPad->Update();
}

