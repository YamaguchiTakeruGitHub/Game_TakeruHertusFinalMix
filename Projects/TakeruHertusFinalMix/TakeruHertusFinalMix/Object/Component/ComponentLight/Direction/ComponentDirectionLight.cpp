#include "ComponentDirectionLight.h"

void ComponentDirectionLight::Init()
{
	lightHandle = CreateDirLightHandle(VGet(0.0f, 300.0f, 0.0f));
}

void ComponentDirectionLight::Update()
{
}

void ComponentDirectionLight::Draw()
{
}

void ComponentDirectionLight::Final()
{
	DeleteLightHandle(lightHandle);
}
