#include "Command.h"

Command::Command()
	: m_isComandSystem(false)
	, m_isShortcutSystem(false)
{
	m_Idm = std::make_shared<InputDeviceManager>();

	AddComponent<ComponentComandSystem>();
	m_comandSystem = GetComponent<ComponentComandSystem>();

	AddComponent<ComponentComandShortcutSystem>();
	m_shortcutSystem = GetComponent<ComponentComandShortcutSystem>();
}

void Command::Init()
{
	m_Idm->Init();
	m_isComandSystem = false;
	m_isShortcutSystem = false;
	Entity::InitComponents();
}

void Command::Update()
{
	m_Idm->Update();

	if (m_Idm->joyPad->isLB == true)
	{
		m_isComandSystem = false;
		m_isShortcutSystem = true;
	}
	else
	{
		m_isComandSystem = true;
		m_isShortcutSystem = false;
	}

	if (m_isComandSystem == true && m_isShortcutSystem == false)
	{
		m_comandSystem->Update();
	}
	if (m_isShortcutSystem == true && m_isComandSystem == false)
	{
		m_shortcutSystem->Update();
	}
	

}

void Command::Draw()
{
	if (m_isComandSystem == true && m_isShortcutSystem == false)
	{
		m_comandSystem->Draw();
	}
	if (m_isShortcutSystem == true && m_isComandSystem == false)
	{
		m_shortcutSystem->Draw();
	}
	
}

void Command::Final()
{
	Entity::FinalComponents();
}
