#include "SceneTitle.h"
#include "SceneManager.h"

SceneTitle::SceneTitle()
	: m_nowSelect(eMenu_LoadGame)
	, m_isDDownButtonPressed(false)
	, m_isDUpButtonPressed(false)
	, m_isChangeSceneGame(false)
	, m_pushBefore(0)
	, m_pushNow(0)

	, m_NewGamePos(VGet(25.0f, 20.0f, 0.0f))
	, m_LoadGamePos(VGet(25.0f, 40.0f, 0.0f))
	, m_BackPos(VGet(25.0f, 60.0f, 0.0f))
	, m_BackGroundPos(VGet(0.0f, 0.0f, 0.0f))
	, m_ButtonPointPos(VGet(0.0f, 20.0f, 0.0f))
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	m_Idm.get()->Init();

	m_nowSelect = eMenu_LoadGame;
	m_isDDownButtonPressed = false;
	m_isDUpButtonPressed = false;
	m_isChangeSceneGame = false;
	m_pushBefore = 0;
	m_pushNow = 0;

	m_NewGamePos = VGet(25.0f, 20.0f, 0.0f);
	m_LoadGamePos = VGet(25.0f, 40.0f, 0.0f);
	m_BackPos = VGet(25.0f, 60.0f, 0.0f);
	m_BackGroundPos = VGet(0.0f, 0.0f, 0.0f);
	m_ButtonPointPos = VGet(0.0f, 20.0f, 0.0f);


}

void SceneTitle::Update()
{
	m_Idm.get()->Update();

	if (m_Idm->joyPad->isDUP == true && !m_isDUpButtonPressed)
	{
		m_isDUpButtonPressed = true;

		m_nowSelect = (m_nowSelect + (eMenu_Num - 1)) % eMenu_Num;
		m_pushNow = 1;
	}
	if (!m_Idm->joyPad->isDUP)
	{
		m_isDUpButtonPressed = false;
	}
	
	if (m_Idm->joyPad->isDDOWN == true && !m_isDDownButtonPressed)
	{
		m_isDDownButtonPressed = true;

		m_nowSelect = (m_nowSelect + 1) % eMenu_Num;
		m_pushNow = 1;
	}
	if (!m_Idm->joyPad->isDDOWN)
	{
		m_isDDownButtonPressed = false;
	}



	
	m_isChangeSceneGame = false;


	
	if (m_Idm->joyPad->isB == true)
	{
		switch (m_nowSelect)
		{
		case eMenu_NewGame:

			SceneManager::GetInstance().ChangeScene(SceneType::Game);

			break;

		case eMenu_LoadGame:
			

			break;

		case eMenu_Back:
			DxLib_End();
			break;
		}
	}

	
	switch (m_nowSelect)
	{
	case eMenu_NewGame:
		m_ButtonPointPos.y = m_NewGamePos.y;
		break;
	case eMenu_LoadGame:
		m_ButtonPointPos.y = m_LoadGamePos.y;
		break;
	case eMenu_Back:
		m_ButtonPointPos.y = m_BackPos.y;
		break;
	}




	if (CheckHitKey(KEY_INPUT_T))
	{
		SceneManager::GetInstance().ChangeScene(SceneType::Game);
	}
	
}

void SceneTitle::Draw()
{
	DebugDraw();

#if _DEBUG
	
	DrawFormatString((int)m_NewGamePos.x, (int)m_NewGamePos.y, 0xffffff, "NewGame");
	DrawFormatString((int)m_LoadGamePos.x, (int)m_LoadGamePos.y, 0xffffff, "LoadGame");
	DrawFormatString((int)m_BackPos.x, (int)m_BackPos.y, 0xffffff, "Back");
	DrawFormatString((int)m_ButtonPointPos.x, (int)m_ButtonPointPos.y, 0xff0000, "Å®");
#endif

}

void SceneTitle::Final()
{
}

void SceneTitle::DebugDraw()
{
#ifdef _DEBUG
	DrawString(0, 0, "TitleScene", 0xffffff, 16);


#endif // _DEBUG

}
