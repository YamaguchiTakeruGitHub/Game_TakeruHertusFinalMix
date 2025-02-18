#include "SceneDebug.h"
#include "../SceneManager.h"

SceneDebug::SceneDebug()
	: m_pos()
	, m_nowSelect(eSelect_Title)
	, m_isDDownButtonPressed(false)
	, m_isDUpButtonPressed(false)
	, m_isChangeSceneGame(false)
	, m_pushBefore(0)
	, m_pushNow(0)

{
	
	m_pos.nowPoint = VGet(0, 40, 0);

	m_pos.Title = VGet(0,40,0);
	m_pos.Game = VGet(0, 60, 0);
	m_pos.Result = VGet(0, 80, 0);
	m_pos.Clear = VGet(0, 100, 0);
	m_pos.Back = VGet(0, 120, 0);

	m_UI = std::make_shared<UIManager>();
}

SceneDebug::~SceneDebug()
{
}

void SceneDebug::Init()
{
	m_Idm.get()->Init();
	m_UI.get()->Init();

	m_nowSelect = eSelect_Title;
	m_isDDownButtonPressed = false;
	m_isDUpButtonPressed = false;
	m_isChangeSceneGame = false;
	m_pushBefore = 0;
	m_pushNow = 0;

	m_pos.nowPoint = VGet(0, 40, 0);

	m_pos.Title = VGet(0, 40, 0);
	m_pos.Game = VGet(0, 60, 0);
	m_pos.Result = VGet(0, 80, 0);
	m_pos.Clear = VGet(0, 100, 0);
	m_pos.Back = VGet(0, 120, 0);
}

void SceneDebug::Update()
{
	m_Idm.get()->Update();
	
	//項目の選択上下
	m_UI->m_select->UpSelect(m_nowSelect, eSelect_Num, m_Idm->joyPad->isDUP == true);
	m_UI->m_select->DownSelect(m_nowSelect, eSelect_Num, m_Idm->joyPad->isDDOWN == true);

	SelectNow();
	SelectPush();
}

void SceneDebug::Draw()
{
	DrawString(40, 0, "DebugScene", 0xfffff);
	DrawString(40, 20, "すべてのシーンに遷移できるよ！", 0xfffff);
	
	DrawFormatString(40, m_pos.Title.y, 0xffffff, "TitleScene");
	DrawFormatString(40, m_pos.Game.y, 0xffffff, "GameScene");
	DrawFormatString(40, m_pos.Result.y, 0xffffff, "ResultScene");
	DrawFormatString(40, m_pos.Clear.y, 0xffffff, "ClearScene");
	DrawFormatString(40, m_pos.Back.y, 0xffffff, "Back");

	DrawFormatString(20, m_pos.nowPoint.y, 0xffffff, "→");
}

void SceneDebug::Final()
{
}

void SceneDebug::SelectPush()
{
	if (m_Idm->joyPad->isB == true)
	{
		switch (m_nowSelect)
		{
		case eSelect_Title:
			SceneManager::GetInstance().ChangeScene(SceneType::Title);
			break;

		case eSelect_Game:
			SceneManager::GetInstance().ChangeScene(SceneType::Game);
			break;

		case eSelect_Result:
			SceneManager::GetInstance().ChangeScene(SceneType::Result);
			break;

		case eSelect_Clear:
			SceneManager::GetInstance().ChangeScene(SceneType::Clear);
			break;

		case eSelect_Back:
			DxLib_End();
			break;
		}
	}
}

void SceneDebug::SelectNow()
{
	switch (m_nowSelect)
	{
	case eSelect_Title:
		m_pos.nowPoint.y = m_pos.Title.y;
		break;

	case eSelect_Game:
		m_pos.nowPoint.y = m_pos.Game.y;
		break;

	case eSelect_Result:
		m_pos.nowPoint.y = m_pos.Result.y;
		break;

	case eSelect_Clear:
		m_pos.nowPoint.y = m_pos.Clear.y;
		break;

	case eSelect_Back:
		m_pos.nowPoint.y = m_pos.Back.y;
		break;
	}
}


