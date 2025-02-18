#include "ComponentComandShortcutSystem.h"

ComponentComandShortcutSystem::ComponentComandShortcutSystem()
	: m_shortcutGraphHandle{-1,-1,-1,-1}
	, m_shortcutGraphPos{ VGet(0, 0, 0), VGet(0, 0, 0), VGet(0, 0, 0), VGet(0, 0, 0) }
	
	, m_isShortcut1(false)
	, m_isShortcut2(false)
	, m_isShortcut3(false)
	
	, m_isB_ButtonPressed(false)
	, m_isX_ButtonPressed(false)
	, m_isY_ButtonPressed(false)
{
	m_Idm = std::make_shared<InputDeviceManager>();
}


void ComponentComandShortcutSystem::Init()
{
	m_Idm->Init();

	m_shortcutGraphHandle[0] = LoadGraph("");
	m_shortcutGraphHandle[1] = LoadGraph("");
	m_shortcutGraphHandle[2] = LoadGraph("");
	m_shortcutGraphHandle[3] = LoadGraph("");

	m_shortcutGraphPos[0] = VGet(0,0,0);
	m_shortcutGraphPos[1] = VGet(0,0,0);
	m_shortcutGraphPos[2] = VGet(0,0,0);
	m_shortcutGraphPos[3] = VGet(0,0,0);

	m_isShortcut1 = false;
	m_isShortcut2 = false;
	m_isShortcut3 = false;

	m_isB_ButtonPressed = false;
	m_isX_ButtonPressed = false;
	m_isY_ButtonPressed = false;

}

void ComponentComandShortcutSystem::Update()
{
	m_isShortcut1 = false;
	m_isShortcut2 = false;
	m_isShortcut3 = false;

	m_Idm->Update();

	if (m_Idm->joyPad->isX == true && !m_isX_ButtonPressed)
	{
		m_isShortcut1 = true;
	}
	if (m_Idm->joyPad->isY == true && !m_isY_ButtonPressed)
	{
		m_isShortcut2 = true;
	}
	if (m_Idm->joyPad->isB == true && !m_isB_ButtonPressed)
	{
		m_isShortcut3 = true;
	}

	if (!m_Idm->joyPad->isX)
	{
		m_isX_ButtonPressed = false;
	}
	if (!m_Idm->joyPad->isY)
	{
		m_isShortcut2 = true;
		m_isY_ButtonPressed = false;
	}
	if (!m_Idm->joyPad->isB)
	{
		m_isShortcut3 = true;
		m_isB_ButtonPressed = false;
	}

}

void ComponentComandShortcutSystem::Draw()
{
	//表示
	DrawGraph(m_shortcutGraphPos[0].x, m_shortcutGraphPos[0].y, m_shortcutGraphHandle[0], true);
	
	DrawCircle(20, 700, 30.0f, 0xffffff, true);
	//コマンドの名前
}

void ComponentComandShortcutSystem::Final()
{
	for (int i = 0; i < 4; i++)
	{
		if (m_shortcutGraphHandle[i] != -1)
		{
			DeleteGraph(m_shortcutGraphHandle[i]);
		}
	}
}
