#include "SceneTitle.h"
#include "../SceneManager.h"
#include <EffekseerForDXLib.h>



SceneTitle::SceneTitle()
	: m_newGamePosition(VGet(0, 40, 0))
	, m_loadGamePosition(VGet(0, 60, 0))
	, m_backPosition(VGet(0, 80, 0))

	, m_buttonPointPosition(VGet(0, 40, 0))
	, m_titleBackGroundPosition(VGet(0, -20, 0))
	, m_titleRogoPosition(VGet(0, 0, 0))
	, m_titleSelectPosition(VGet(0, 0, 0))
	, m_titleOPPPosition(VGet(0, 0, 0))
	
	, m_titleBackGroundGraphHandle(-1)
	, m_buttonPointGraphHandle(-1)
	, m_titleRogoGraphHandle(-1)
	, m_titleSelectGraphHandle(-1)
	, m_titleOPPGraphHandle(-1)

	, m_titleSelectNewGameGraphHandle(-1)
	, m_titleSelectLoadGraphHandle(-1)
	, m_titleSelectBackGraphHandle(-1)
	, m_nowSelect(eSelect_NewGame)
	, m_isDDownButtonPressed(false)
	, m_isDUpButtonPressed(false)
	, m_pushBefore(0)
	, m_pushNow(0)

	  /*フェードイン*/
	, m_fadeAlpha(0.0f)
	  /*BGM・SE*/
	, m_bgmHandle(0)
	, m_seHandle(0)
	  /*LoadGameデータ*/
	, isLoadGame(false)
	, loadGameBackGroundGraphHandle(-1)
	, loadGameBackGroundGraphPosition(VGet(0,0,0))
	, easingTime(0.0f)
	
	//選択肢の背景
	, loadGameMenuSelectBackGroundGraphHandle(-1)//ロードする選択肢の背景画像
	, loadGameMenuSelectBackGroundPosition(VGet(0,0,0))//ロードする選択肢の背景座標

	, m_loadGameMenuSelectNowSelect(eLGM_Select_1)

	//パーティクル
	, m_selectParticle(-1)

	  /*NewGameデータ*/
	, isNewGame(false)
{
	

	m_UI = std::make_shared<UIManager>();
	m_Idm = std::make_shared<InputDeviceManager>();

	/*テスト*/
	circlePos = VGet(0, 0, 0);
	time = 0.0f;
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::InitResource()
{
	

	/*画像のリソース*/
	m_titleBackGroundGraphHandle = LoadGraph("../Asset/2D/Title/TitleBackGround.png");
	m_buttonPointGraphHandle = LoadGraph("../Asset/2D/Title/buttonPoint.png");
	m_titleRogoGraphHandle = LoadGraph("../Asset/2D/Title/TitleRogo.png");
	m_titleSelectGraphHandle = LoadGraph("../Asset/2D/Title/TitleSelect.png");

	m_titleOPPGraphHandle = LoadGraph("../Asset/2D/Title/TitleOPP.png");

	m_titleSelectNewGameGraphHandle = LoadGraph("../Asset/2D/Title/TitleSelectNewGame.png");
	m_titleSelectLoadGraphHandle = LoadGraph("../Asset/2D/Title/TitleSelectLoad.png");
	m_titleSelectBackGraphHandle = LoadGraph("../Asset/2D/Title/TitleSelectBack.png");

	/*LoadGameリソース*/
	loadGameBackGroundGraphHandle = LoadGraph("../Asset/2D/Title/LoadGameGraph/LoadGameBackGround.png");

	loadGameMenuGraphHandle[0] = LoadGraph("../Asset/2D/Title/LoadGameGraph/LoadMenuDown.png");
	loadGameMenuGraphHandle[1] = LoadGraph("../Asset/2D/Title/LoadGameGraph/LoadMenuUP.png");
	loadGameMenuGraphHandle[2] = LoadGraph("../Asset/2D/Title/LoadGameGraph/LoadMenuText1.png");
	loadGameMenuGraphHandle[3] = LoadGraph("../Asset/2D/Title/LoadGameGraph/LoadMenuText2.png");

	//セレクトの背景
	loadGameMenuSelectBackGroundGraphHandle = LoadGraph("../Asset/2D/Title/LoadGameGraph/LoadMenuSelect/LoadMenuSelectBackGround.png");

	//セレクト番号
	loadGameMenuSelectNumberGraphHandle[0] = LoadGraph("../Asset/2D/Title/LoadGameGraph/LoadMenuSelect/LoadMenuSelectNumber_1.png");
	loadGameMenuSelectNumberGraphHandle[1] = LoadGraph("../Asset/2D/Title/LoadGameGraph/LoadMenuSelect/LoadMenuSelectNumber_2.png");
	loadGameMenuSelectNumberGraphHandle[2] = LoadGraph("../Asset/2D/Title/LoadGameGraph/LoadMenuSelect/LoadMenuSelectNumber_3.png");
	loadGameMenuSelectNumberGraphHandle[3] = LoadGraph("../Asset/2D/Title/LoadGameGraph/LoadMenuSelect/LoadMenuSelectNumber_4.png");

	//セレクト非選択状態
	loadGameMenuSelectGraphHandle[0] = LoadGraph("../Asset/2D/Title/LoadGameGraph/LoadMenuSelect/LoadMenuSelect_1.png");
	loadGameMenuSelectGraphHandle[1] = LoadGraph("../Asset/2D/Title/LoadGameGraph/LoadMenuSelect/LoadMenuSelect_2.png");
	loadGameMenuSelectGraphHandle[2] = LoadGraph("../Asset/2D/Title/LoadGameGraph/LoadMenuSelect/LoadMenuSelect_3.png");
	loadGameMenuSelectGraphHandle[3] = LoadGraph("../Asset/2D/Title/LoadGameGraph/LoadMenuSelect/LoadMenuSelect_4.png");

	//セレクト選択状態
	loadGameMenuSelectOnGraphHandle[0] = LoadGraph("../Asset/2D/Title/LoadGameGraph/LoadMenuSelect/LoadMenuSelectOn_1.png");
	loadGameMenuSelectOnGraphHandle[1] = LoadGraph("../Asset/2D/Title/LoadGameGraph/LoadMenuSelect/LoadMenuSelectOn_2.png");
	loadGameMenuSelectOnGraphHandle[2] = LoadGraph("../Asset/2D/Title/LoadGameGraph/LoadMenuSelect/LoadMenuSelectOn_3.png");
	loadGameMenuSelectOnGraphHandle[3] = LoadGraph("../Asset/2D/Title/LoadGameGraph/LoadMenuSelect/LoadMenuSelectOn_4.png");

	//セレクトパーティクル
	m_selectParticle = LoadGraph("../Asset/2D/Title/SelectParticles.png");

	/*BGM・SEのリソース*/
	m_bgmHandle = LoadSoundMem("../Asset/Sound/Title/TitleBGM.mp3");
	m_seHandle = LoadSoundMem("../Asset/Sound/Title/TitleSelectSE.mp3");
}

void SceneTitle::Init()
{
	//リソースの量
	resourceNum = 10;
	/*非同期読み込み*/
	SetUseASyncLoadFlag(true);
	InitResource();
	SetUseASyncLoadFlag(false);

	isLoading = true;
	isTitlePlayeing = false;

	m_Idm->Init();
	m_UI->Init();

	m_newGamePosition = VGet(27, 535, 0);
	m_loadGamePosition = VGet(27, 598, 0);
	m_backPosition = VGet(27, 663, 0);
	m_buttonPointPosition = VGet(27, 535, 0);

	m_titleBackGroundPosition = VGet(0, 0, 0);
	m_titleRogoPosition = VGet(0, 0, 0);
	m_titleSelectPosition = VGet(0, 0, 0);
	m_titleOPPPosition = VGet(800, 30, 0);

	m_nowSelect = eSelect_NewGame;

	m_isDDownButtonPressed = false;
	m_isDUpButtonPressed = false;

	m_pushBefore = 0;
	m_pushNow = 0;
	m_pushCutTime = 0;

	/*テスト*/
	circlePos = VGet(600, 320, 0);
	time = 0.0f;

	/*フェードイン*/
	m_fadeAlpha = 0.0f;

	/*LoadGame*/
	isLoadGame = false;
	loadGameBackGroundGraphPosition = VGet(0,0,0);
	loadGameMenuSelectBackGroundPosition = VGet(0, 0, 0);

	loadGameMenuPos[0] = VGet(0, 0, 0);
	loadGameMenuPos[1] = VGet(0, 0, 0);
	loadGameMenuPos[2] = VGet(0, 0, 0);
	loadGameMenuPos[3] = VGet(0, 0, 0);

	//セレクトの背景
	loadGameMenuSelectBackGroundPosition = VGet(0, 0, 0);

	//セレクト番号
	loadGameMenuSelectNumberPosition[0] = VGet(0, 0, 0);
	loadGameMenuSelectNumberPosition[1] = VGet(0, 0, 0);
	loadGameMenuSelectNumberPosition[2] = VGet(0, 0, 0);
	loadGameMenuSelectNumberPosition[3] = VGet(0, 0, 0);

	//セレクト非選択状態
	loadGameMenuSelectPosition[0] = VGet(0, 0, 0);
	loadGameMenuSelectPosition[1] = VGet(0, 0, 0);
	loadGameMenuSelectPosition[2] = VGet(0, 0, 0);
	loadGameMenuSelectPosition[3] = VGet(0, 0, 0);

	//セレクト選択状態
	loadGameMenuSelectOnPosition[0] = VGet(0, 0, 0);
	loadGameMenuSelectOnPosition[1] = VGet(0, 0, 0);
	loadGameMenuSelectOnPosition[2] = VGet(0, 0, 0);
	loadGameMenuSelectOnPosition[3] = VGet(0, 0, 0);

	m_loadGameMenuSelectNowSelect = eLGM_Select_1;

	easingTime = 0.0f;

	/*NewGame*/
	isNewGame = false;
}

void SceneTitle::Update()
{
	m_Idm->Update();

	if (isLoading)
	{
		if (GetASyncLoadNum() == 0)
		{
			isLoading = false;
		}

		if (time >= 60.0f)
		{
			time = 0.0f;
		}
		else
		{
			time += 0.1f;
		}

		circlePos = VGet(1150 + 50 * cosf(time) / DX_PI_F,
			650 + 50 * sinf(time) / DX_PI_F,
			0);

	}
	else
	{
		if (m_Idm->joyPad->isB == true)
		{
			isTitlePlayeing = true;
		}
	}

	if (isTitlePlayeing == true)
	{
		//BGMの更新
		BGM_Update();
		if (isLoadGame == true)
		{
			LoadGameUpdate();
		}

		if(/*!isNewGame || */!isLoadGame)
		{
			//タイトル画面の更新処理
			TitleUpdate();
			easingTime = 0.0f;
		}
	}

}

void SceneTitle::Draw()
{
	if (isLoading)
	{
		DrawString(240, 200, "Now Loading...", 0xffffff);
		DrawCircle(circlePos.x, circlePos.y, 10, 0xffa500, true);
	}
	else
	{
		DrawString(240, 200, "Loding Completed!", 0xffffff);
		DrawString(240, 220, "PushBotton<B>", 0xffffff);
	}

	if (isTitlePlayeing == true)
	{
		//タイトル画面の描画
		TitleDraw();
		
		if (isLoadGame == true)
		{
			LoadGameDraw();
		}
	}
}

void SceneTitle::Final()
{
	DeleteGraph(m_titleBackGroundGraphHandle);
	DeleteGraph(m_buttonPointGraphHandle);
	DeleteGraph(m_titleRogoGraphHandle);
	DeleteGraph(m_titleSelectGraphHandle);

	DeleteGraph(m_titleOPPGraphHandle);

	DeleteGraph(m_titleSelectNewGameGraphHandle);
	DeleteGraph(m_titleSelectLoadGraphHandle);
	DeleteGraph(m_titleSelectBackGraphHandle);

	/*LoadGameリソース*/
	DeleteGraph(loadGameBackGroundGraphHandle);

	for (int i = 0; i < 4; i++)
	{
		if (loadGameMenuGraphHandle[i] != -1)//グラフに何か入っていれば
		{
			DeleteGraph(loadGameMenuGraphHandle[i]);
		}
	}

	//セレクトの背景
	DeleteGraph(loadGameMenuSelectBackGroundGraphHandle);

	//セレクト番号
	for (int i = 0; i < 4; i++)
	{
		if (loadGameMenuSelectNumberGraphHandle[i] != -1)//グラフに何か入っていれば
		{
			DeleteGraph(loadGameMenuSelectNumberGraphHandle[i]);
		}
	}

	//セレクト非選択状態
	for (int i = 0; i < 4; i++)
	{
		if (loadGameMenuSelectGraphHandle[i] != -1)//グラフに何か入っていれば
		{
			DeleteGraph(loadGameMenuSelectGraphHandle[i]);
		}
	}

	//セレクト選択状態
	for (int i = 0; i < 4; i++)
	{
		if (loadGameMenuSelectOnGraphHandle[i] != -1)//グラフに何か入っていれば
		{
			DeleteGraph(loadGameMenuSelectOnGraphHandle[i]);
		}
	}

	DeleteGraph(m_selectParticle);

	DeleteSoundMem(m_bgmHandle);
	DeleteSoundMem(m_seHandle);
}

void SceneTitle::SelectPush()
{
	if (m_pushCutTime >= 50)
	{
		m_pushCutTime = 50;

		if (m_Idm->joyPad->isB == true || CheckHitKey(KEY_INPUT_ESCAPE))
		{
			switch (m_nowSelect)
			{
			case eSelect_NewGame:
				SceneManager::GetInstance().ChangeScene(SceneType::Game);
				isNewGame = true;
				break;
			case eSelect_LoadGame:
				//SceneManager::GetInstance().ChangeScene(SceneType::Game);
				isLoadGame = true;

				break;
			case eSelect_Back:
				Effkseer_End();
				DxLib_End();
				break;
			}
		}
	}
	else
	{
		m_pushCutTime++;
	}



}

void SceneTitle::SelectNow()
{
	switch (m_nowSelect)
	{
	case eSelect_NewGame:
		m_buttonPointPosition.y = m_newGamePosition.y;
		break;
	case eSelect_LoadGame:
		m_buttonPointPosition.y = m_loadGamePosition.y;
		break;
	case eSelect_Back:
		m_buttonPointPosition.y = m_backPosition.y;
		break;
	}
}

void SceneTitle::SelectEfect()
{
	/*セレクトエフェクト*/
	circlePos = VGet(250 + 50 * cosf(time) / DX_PI_F,
		250 + 50 * sinf(time) / DX_PI_F,
		0);

	switch (m_nowSelect)
	{
	case eSelect_NewGame:
		/*セレクトエフェクト*/
		circlePos = VGet(30 + 50 * cosf(time) / DX_PI_F,
			530 + 50 * sinf(time) / DX_PI_F,
			0);
		break;
	case eSelect_LoadGame:
		/*セレクトエフェクト*/
		circlePos = VGet(30 + 50 * cosf(time) / DX_PI_F,
			590 + 50 * sinf(time) / DX_PI_F,
			0);
		break;
	case eSelect_Back:
		/*セレクトエフェクト*/
		circlePos = VGet(30 + 50 * cosf(time) / DX_PI_F,
			660 + 50 * sinf(time) / DX_PI_F,
			0);
		break;
	}
}

void SceneTitle::BGM_Update()
{
	//音量調整
	ChangeVolumeSoundMem(100, m_bgmHandle);
	//BGM
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP, false);
}

void SceneTitle::TitleUpdate()
{
	//音量調整
	ChangeVolumeSoundMem(255, m_seHandle);

	//選択処理
	m_UI->m_select->UpSelect(m_nowSelect, eSelect_Num, m_Idm->joyPad->isDUP == true);
	m_UI->m_select->DownSelect(m_nowSelect, eSelect_Num, m_Idm->joyPad->isDDOWN == true);

	/*テスト*/
	if (time >= 60.0f)
	{
		time = 0.0f;
	}
	else
	{
		time += 0.04f;
	}

	if (m_nowSelect != m_prevSelect)
	{
		m_fadeAlpha = 0.0f;
		m_prevSelect = m_nowSelect;
		PlaySoundMem(m_seHandle, DX_PLAYTYPE_BACK, true);
	}

	if (m_fadeAlpha < 255.0f)
	{
		m_fadeAlpha += 8.0f;
	}
	else
	{
		m_fadeAlpha = 255.0f;
	}

	SelectEfect();

	SelectNow();
	SelectPush();

}

void SceneTitle::TitleDraw()
{

#ifdef _DEBUG
	DrawString(0, 0, "TitleScene", 0xfffff);
	DrawFormatString(40, m_newGamePosition.y, 0xffffff, "NewGame");
	DrawFormatString(40, m_loadGamePosition.y, 0xffffff, "LoadGame");
	DrawFormatString(40, m_backPosition.y, 0xffffff, "Back");
	DrawFormatString(20, m_buttonPointPosition.y, 0xffffff, "→");
#endif // _DEBUG

	DrawGraph(m_titleBackGroundPosition.x, m_titleBackGroundPosition.y, m_titleBackGroundGraphHandle, true);
	DrawGraph(m_titleRogoPosition.x, m_titleRogoPosition.y, m_titleRogoGraphHandle, true);
	DrawGraph(m_titleSelectPosition.x, m_titleSelectPosition.y, m_titleSelectGraphHandle, true);
	DrawGraph(m_buttonPointPosition.x, m_buttonPointPosition.y, m_buttonPointGraphHandle, true);
	DrawGraph(m_titleOPPPosition.x, m_titleOPPPosition.y, m_titleOPPGraphHandle, true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);

	switch (m_nowSelect)
	{
	case eSelect_NewGame:
		DrawGraph(0.0f, -6.0f, m_titleSelectNewGameGraphHandle, true);

		break;
	case eSelect_LoadGame:
		DrawGraph(0.0f, -6.0f, m_titleSelectLoadGraphHandle, true);

		break;
	case eSelect_Back:
		DrawGraph(0.0f, -6.0f, m_titleSelectBackGraphHandle, true);

		break;
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	/*テスト*/
	//DrawCircle(circlePos.x, circlePos.y, 6, 0xffa500, true);
	DrawGraph(circlePos.x - 5, circlePos.y, m_selectParticle, true);

}

void SceneTitle::LoadGameUpdate()
{
	if (m_Idm->joyPad->isA == true)
	{
		isLoadGame = false;
	}

	m_UI->m_select->UpSelect(m_loadGameMenuSelectNowSelect, eLGM_Select_Num, m_Idm->joyPad->isDUP == true);
	m_UI->m_select->DownSelect(m_loadGameMenuSelectNowSelect, eLGM_Select_Num, m_Idm->joyPad->isDDOWN == true);


	if (easingTime >= 100)
	{
		easingTime = 100;
	}
	else
	{
		easingTime += 1.0f;
	}

	/*for (int i = 0; i < 4; i++)
	{
		
		loadGameMenuPos[i].y = 100.0f - m_easing.OutBounce(easingTime, 100, 100, 0);
	}*/

	loadGameMenuPos[0].y = 200.0f - m_easing.Linear(easingTime, 100, 200, 1);
	loadGameMenuPos[1].y = m_easing.InQuad(easingTime, 100, 0, -100);

	loadGameMenuPos[2].y = 200.0f - m_easing.Linear(easingTime, 100, 200, 1);
	loadGameMenuPos[3].y = m_easing.InQuad(easingTime, 100, 0, -100);

	loadGameMenuPos[2].x = 100.0f - m_easing.OutBounce(easingTime, 100, 100, 1);
	loadGameMenuPos[3].x = 100.0f - m_easing.OutBounce(easingTime, 100, 100, 1);

}

void SceneTitle::LoadGameDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155);
	DrawGraph(loadGameBackGroundGraphPosition.x, loadGameBackGroundGraphPosition.y, loadGameBackGroundGraphHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawGraph(loadGameMenuSelectBackGroundPosition.x, loadGameMenuSelectBackGroundPosition.y, loadGameMenuSelectBackGroundGraphHandle, true);

	//非選択状態
	for (int i = 0; i < 4; i++)
	{
		if (loadGameMenuSelectGraphHandle[i] != -1)
		{
			DrawGraph(loadGameMenuSelectPosition[i].x, loadGameMenuSelectPosition[i].y, loadGameMenuSelectGraphHandle[i], true);
		}
	}

	switch (m_loadGameMenuSelectNowSelect)
	{
	case eLGM_Select_1:
		DrawGraph(loadGameMenuSelectOnPosition[0].x, loadGameMenuSelectOnPosition[0].y, loadGameMenuSelectOnGraphHandle[0], true);
		/*セレクトエフェクト*/
		circlePos = VGet(280 + 50 * cosf(time) / DX_PI_F,
			150 + 50 * sinf(time) / DX_PI_F,
			0);
		break;

	case eLGM_Select_2:
		DrawGraph(loadGameMenuSelectOnPosition[1].x, loadGameMenuSelectOnPosition[1].y, loadGameMenuSelectOnGraphHandle[1], true);
		/*セレクトエフェクト*/
		circlePos = VGet(280 + 50 * cosf(time) / DX_PI_F,
			260 + 50 * sinf(time) / DX_PI_F,
			0);
		break;

	case eLGM_Select_3:
		DrawGraph(loadGameMenuSelectOnPosition[2].x, loadGameMenuSelectOnPosition[2].y, loadGameMenuSelectOnGraphHandle[2], true);
		/*セレクトエフェクト*/
		circlePos = VGet(280 + 50 * cosf(time) / DX_PI_F,
			360 + 50 * sinf(time) / DX_PI_F,
			0);
		break;

	case eLGM_Select_4:
		DrawGraph(loadGameMenuSelectOnPosition[3].x, loadGameMenuSelectOnPosition[3].y, loadGameMenuSelectOnGraphHandle[3], true);
		/*セレクトエフェクト*/
		circlePos = VGet(280 + 50 * cosf(time) / DX_PI_F,
			460 + 50 * sinf(time) / DX_PI_F,
			0);
		break;
	}

	if (m_Idm->joyPad->isB == true)
	{
		switch (m_loadGameMenuSelectNowSelect)
		{
		case eLGM_Select_1:

			break;

		case eLGM_Select_2:
			//SceneManager::GetInstance().ChangeScene(SceneType::Game);

			break;

		case eLGM_Select_3:

			break;

		case eLGM_Select_4:

			break;
		}
	}

	//選択状態
	/*for (int i = 0; i < 4; i++)
	{
		if (loadGameMenuSelectOnGraphHandle[i] != -1)
		{
			DrawGraph(loadGameMenuSelectOnPosition[i].x, loadGameMenuSelectOnPosition[i].y, loadGameMenuSelectOnGraphHandle[i], true);
		}
	}*/

	//番号
	for (int i = 0; i < 4; i++)
	{
		if (loadGameMenuSelectNumberGraphHandle[i] != -1)
		{
			DrawGraph(loadGameMenuSelectNumberPosition[i].x, loadGameMenuSelectNumberPosition[i].y, loadGameMenuSelectNumberGraphHandle[i], true);
		}
	}

	//top&down%text&text
	for (int i = 0; i < 4; i++)
	{
		if (loadGameMenuGraphHandle[i] != -1)
		{
			DrawGraph(loadGameMenuPos[i].x, loadGameMenuPos[i].y, loadGameMenuGraphHandle[i], true);
		}
	}


	if (time >= 60.0f)
	{
		time = 0.0f;
	}
	else
	{
		time += 0.1f;
	}

	
	//DrawCircle(circlePos.x, circlePos.y, 10, 0xffa500, true);
	DrawGraph(circlePos.x - 5, circlePos.y, m_selectParticle, true);
#ifdef _DEBUG
	DrawFormatString(20,20, 0xffffff, "LoadGame画面だお");
#endif // _DEBUG


}
