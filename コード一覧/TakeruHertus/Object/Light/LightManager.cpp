#include "LightManager.h"


LightManager::LightManager()
	: m_DirLight()
{
	m_DirLight.handle = -1;
	m_DirLight.postion = VGet(-1.0f, 0.0f, -1.0f);
}

LightManager::~LightManager()
{
	DeleteLightHandle(m_DirLight.handle);
}

void LightManager::Init()
{
	m_DirLight.postion = VGet(-1.0f, 0.0f, -1.0f);
	m_DirLight.handle = CreateDirLightHandle(m_DirLight.postion);
}

void LightManager::Update()
{
}

void LightManager::Draw()
{
}

void LightManager::Final()
{
	DeleteLightHandle(m_DirLight.handle);
}
