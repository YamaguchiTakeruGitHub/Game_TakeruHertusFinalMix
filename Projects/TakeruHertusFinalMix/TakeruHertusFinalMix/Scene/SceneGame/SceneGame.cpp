#include "SceneGame.h"
#include "../SceneManager.h"


SceneGame::SceneGame()
	: m_tutorialSectionNumber(0)
	, m_isSectionSkip(false)
	, m_fadeAlpha(0.0f)

	, m_SelectWeponMyPower(0)
	, m_SelectWeponGivPower(0)
	

	, m_sectionTime(0.0f)
	, m_section_2Time(0.0f)
	, m_isSection_2FowerdBoxEvent(false)
	, m_isSection_2LeftBoxEvent(false)
	, m_isSection_2RightBoxEvent(false)
	, m_section_2EventTime(0.0f)
	, m_section_2EventMaxTime(0.0f)

	, m_section_3Time(0.0f)
	, m_section_3MaxTime(0.0f)
	
	, m_nextSectionPosition(VGet(0,0,0))
	, m_nextSectionRadius(0.0f)
	//テスト
	, mt_effecthandle(-1)
	, mt_playEffectHandle(-1)
{
	//プレイヤー
	m_player = std::make_shared<Player>();

	//カメラ
	m_camera = std::make_shared<Camera>();

	//チュートリアルマップ
	m_mapTutorial = std::make_shared<MapTutorial>();

	//スカイドーム
	m_skyDome = std::make_shared<SkyDome>();

	//ライト
	m_light = std::make_shared<Light>();

	//狐
	m_enemyFox = std::make_shared<Enemy_Fox>();
	
	//ドラゴン敵
	m_enemyDoragon = std::make_shared<Enemy_Doragon>();

	//TS剣
	m_tsSword = std::make_shared<TSSword>();

	//TS盾
	m_tsShield = std::make_shared<TSShield>();

	//TS杖
	m_tsRod = std::make_shared<TSRod>();

	//エフェクト
	m_effect = std::make_shared<ObjectEffecter>();

	//コマンド
	m_command = std::make_shared<Command>();

	//当たり判定
	m_collision = std::make_shared<Collision>();

	//ui
	m_Ui = std::make_shared<UIManager>();

	m_savePoint = std::make_shared<SavePoint>();

	m_LeftBox.m_position = VGet(0,0,0);
	m_LeftBox.m_size = VGet(0, 0, 0);
	
	m_RightBox.m_position = VGet(0, 0, 0);
	m_RightBox.m_size = VGet(0, 0, 0);

	m_FowerdBox.m_position = VGet(0, 0, 0);
	m_FowerdBox.m_size = VGet(0, 0, 0);
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
#ifdef _DEBUG
	DebugInit();
#else
	m_Idm->Init();

	//外部ファイルの読み込み
	std::string GameScenefilename = "../GameData/EventData/EventData_TutorialSection.csv";
	std::vector<std::vector<std::string>> GameSceneData = CSVLib::ReadCSV(GameScenefilename);


	nowWorld = eWorld_Tutorial;
	m_isSectionSkip = false;
	m_fadeAlpha = 0.0f;

	m_sectionTime = 0.0f;
	m_sectionMaxTime = CSVLib::GetCell_float(GameSceneData, 2, 3);

	m_section_2Time = 0.0f;
	m_section_2MaxTime = CSVLib::GetCell_float(GameSceneData, 3,3);

	m_section_3Time = 0.0f;
	m_section_3MaxTime = CSVLib::GetCell_float(GameSceneData, 5, 3);
	m_section_3FinalAnserTime = 0.0f;
	m_fadeAlpha_1 = 0.0f;
	m_fadeAlpha_2 = 0.0f;

	/*セクション２の武器選択のイベント*/

	m_isSection_2FowerdBoxEvent = false;
	m_isSection_2LeftBoxEvent = false;
	m_isSection_2RightBoxEvent = false;
	m_isSection_2SelectFlag = false;
	m_section_2EventTime = 0.0f;
	m_section_2EventMaxTime = CSVLib::GetCell_float(GameSceneData,4, 3);

	nowSelectWepon = eSelectWepon_YES;
	selectWeponYesPos = VGet(1000, 570, 0);
	selectWeponNoPos = VGet(1000, 610, 0);
	selectWeponPointPos = VGet(980, 570, 0);
	selectWeponNextPointPos = VGet(1000, 610, 0);
	selectWeponBackGroundPos = VGet(0, 0, 0);

	/*BGM・SEのリソース*/
	m_bgmHandle = LoadSoundMem("../Asset/Sound/Title/GameBGM.mp3");
	m_seHandle = LoadSoundMem("../Asset/Sound/RunSE/runSE.mp3");

	/*セクション２で出る箱*/
	m_LeftBox.m_position = VGet(-700, 0, 700);
	m_LeftBox.m_size = VGet(150, 150, 150);

	m_RightBox.m_position = VGet(700, 0, 700);
	m_RightBox.m_size = VGet(150, 150, 150);

	m_FowerdBox.m_position = VGet(0, 0, 1400);
	m_FowerdBox.m_size = VGet(150, 150, 150);

	/*セクション3での選択フラグ*/
	m_isSection_3LeftBoxEvent = false;
	m_isSection_3FowerdBoxEvent = false;
	m_isSection_3RightBoxEvent = false;
	m_isSection_3FinalAnser = false;
	m_isSection_3SelectFlag = false;


	/*セクション４の変数初期化（start）*/
	m_section_4EventTime = 0.0f;
	m_section_4EventMaxTime = CSVLib::GetCell_float(GameSceneData, 6, 3);

	m_fadeAlpha_Section4_1 = 0.0f;

	m_section_4EventTime_2 = 0.0f;
	m_section_4EventMaxTime_2 = CSVLib::GetCell_float(GameSceneData, 7, 3);

	m_isSavePointEvent = false;
	m_savePointEventPushBottonTime = 0.0f;
	m_sectionChangeAlpher = 0.0f;
	m_saveClearEventTime = 0.0f;
	/*セクション４の変数初期化 (end)*/

	
	/*Save*/
	m_savePoint->Init();
	isSavePoint = false;
	m_savePointCount = 0;

	/*チュートリアル*/
	TutorialResous();//チュートリアルのリソース
	TutorialInit();//チュートリアルの初期化

	/*町*/
	SevenWondersTownInit();
#endif // _DEBUG
}

void SceneGame::Update()
{
	m_Idm->Update();
#ifdef _DEBUG
	DebugUpdate();
#else
	if (isSavePoint == false)
	{
		//現在どのワールドにいるか
		switch (nowWorld)
		{
		case eWorld_Tutorial:
			TutorialUpdate();
			break;
		case eWorld_SevenWondersTown:
			SevenWondersTownUpdate();
			break;
		}
	}
	else
	{
		m_savePoint->Update();
		isSavePoint = m_savePoint->GetIsSaving();
		m_savePointCount = 1;
	}


#endif // _DEBUG
}

void SceneGame::Draw()
{
#ifdef _DEBUG
	DebugDraw();

#else
	if (isSavePoint == false)
	{
		//現在どのワールドにいるか
		switch (nowWorld)
		{
		case eWorld_Tutorial:
			TutorialDraw();
			break;
		case eWorld_SevenWondersTown:
			SevenWondersTownDraw();
			break;
		}
	}
	else
	{
		m_savePoint->Draw();
	}
	
	//DrawFormatString(800, 20, 0xffffff, "FPS:%f", GetFPS());
#endif // _DEBUG
}

void SceneGame::Final()
{
#ifdef _DEBUG
	DebugFinal();
#else
	TutorialFinal();
	SevenWondersTownFinal();
	m_savePoint->Final();
#endif // _DEBUG
}

void SceneGame::PolygonInit()
{
	/*ポリゴンのテスト*/
	//メッシュ関連

	MV1SetupReferenceMesh(m_mapTutorial->GetModelHandle(), -1, true);

	m_mapTutorial->SetPolygonList(MV1GetReferenceMesh(m_mapTutorial->GetModelHandle(), -1, true));

	int num = m_mapTutorial->GetPolygonList().PolygonNum;
	for (int i = 0; i < num; i++)
	{
		auto poly = m_mapTutorial->GetPolygonList().Polygons[i];

		for (int p = 0; p < 3; p++)
		{
			//頂点の要素番号を取得
			int vIndex = poly.VIndex[p];

			//取得した頂点の要素番号を使って、頂点情報を取得
			auto verRef = m_mapTutorial->GetPolygonList().Vertexs[vIndex];

			//頂点情報へ変換
			VERTEX3D v;
			v.pos = verRef.Position;
			v.dif = verRef.DiffuseColor;
			v.spc = verRef.SpecularColor;
			v.norm = verRef.Normal;
			v.u = verRef.TexCoord[0].u;
			v.v = verRef.TexCoord[0].v;

			//動的配列に格納
			vertexs.emplace_back(v);
		}
	}

}

void SceneGame::PolygoUpdate(int _modelHandle)
{
	/*ポリゴンのテスト*/
	//MEMO:現在当たり判定を設計中プレイヤーの位置更新を訂正
	/*衝突系（球体）*/
	
	//個々のHitPolyDimに毎回当たり判定のチェックがはいるせいでメモリが右肩上がり
	//上記の問題、配列が原因なので設計の見直しが必要


	for (int hitNUM = 0; hitNUM < 1; hitNUM++)
	{
		//HitPolyDim[0] = MV1CollCheck_Sphere(m_mapTutorial->GetModelHandle(), -1, m_player->GetPosition(), m_player->GetRadius());
		HitPolyDim[0] = MV1CollCheck_Sphere(_modelHandle, -1, m_player->GetPosition(), m_player->GetRadius());

		//HitPolyDim[1] = MV1CollCheck_Sphere(m_mapTutorial->GetModelHandle(), -1, m_enemyFox->GetPosition(), m_enemyFox->GetRadius());
		

		bool isOnGround = false;
		bool isOnWall = false;


		if (HitPolyDim[hitNUM].HitNum >= 1)
		{
			for (int i = 0; i < HitPolyDim[hitNUM].HitNum; i++)
			{

				if (hitNUM == 0)
				{
					//m_player->SetPosition(VGet(m_player->GetPosition().x, HitPolyDim[0].Dim[i].HitPosition.y + m_player->GetRadius() - 0.1f, m_player->GetPosition().z));
					//m_player->SetIsGround(true);
					//m_player->SetPosition(VGet(m_player->GetPosition().x, HitPolyDim[0].Dim[i].HitPosition.y + m_player->GetRadius() + 55, m_player->GetPosition().z));
				
					// 接触点の座標を取得
					VECTOR hitPosition = HitPolyDim[0].Dim[i].HitPosition;

					// プレイヤーの位置を補正
					VECTOR correctedPosition = m_player->GetPosition();

					// y軸に平行な面の場合、y軸方向の補正をしない
					if (HitPolyDim[0].Dim[i].Normal.y <= 0.00000001f)  // y軸に平行な面（壁）
					{
						// 壁の法線方向を取得（正規化）
						VECTOR normal = HitPolyDim[0].Dim[i].Normal;
						normal = VNorm(normal);  // 法線ベクトルを正規化

						// プレイヤーの現在位置とヒット位置からスライドベクトルを計算
						VECTOR slideDirection = VSub(m_player->GetPosition(), hitPosition);  // プレイヤーの位置からヒット位置を引いたベクトル
						slideDirection = VNorm(slideDirection);  // プレイヤーとヒット位置を結ぶベクトルを正規化

						// 法線方向にスライド
						VECTOR slideVelocity = VScale(normal, 4.8f);  // スライド速度（調整可能）

						// プレイヤーの新しい位置を計算（壁に沿ってスライド）
						correctedPosition = VAdd(m_player->GetPosition(), slideVelocity);
					}
					else
					{
						// y軸方向の補正（地面に接触した場合）
						correctedPosition.y = hitPosition.y + m_player->GetRadius() - 0.1f;

						// x軸とz軸方向の補正（地面に合わせて位置を補正）
						correctedPosition.x = hitPosition.x;
						correctedPosition.z = hitPosition.z;

						// x軸方向の補正（進む方向に補正）
						if (correctedPosition.x > m_player->GetPosition().x) {
							correctedPosition.x = m_player->GetPosition().x - 0.1f;
						}
						else if (correctedPosition.x < m_player->GetPosition().x) {
							correctedPosition.x = m_player->GetPosition().x + 0.1f;
						}

						// z軸方向の補正（進む方向に補正）
						if (correctedPosition.z > m_player->GetPosition().z) {
							correctedPosition.z = m_player->GetPosition().z - 0.1f;
						}
						else if (correctedPosition.z < m_player->GetPosition().z) {
							correctedPosition.z = m_player->GetPosition().z + 0.1f;
						}
					}

					// プレイヤーの位置を補正
					m_player->SetPosition(correctedPosition);

					// 地面に接触しているので isGround = true
					m_player->SetIsGround(true);
				}

				/*if (hitNUM == 1)
				{
					m_enemyFox->SetPosition(VGet(m_enemyFox->GetPosition().x, HitPolyDim[1].Dim[i].HitPosition.y + m_enemyFox->GetRadius() - 0.1f, m_enemyFox->GetPosition().z));
				}*/
			}
		}
		else
		{
			if (hitNUM == 0 && !isOnGround && !isOnWall && !m_player->GetIsJump())
			{
				m_player->SetIsGround(false);
			}
		}

		MV1CollResultPolyDimTerminate(HitPolyDim[hitNUM]);
	}


}

void SceneGame::CheckSpawnTriggers()
{
	/*for (int i = 0; i < spawnEnemyManager->GetSpawnPointCount(); i++)
	{
		if (spawnEnemyManager->IsPlayerInSpawnZone(m_player->GetPosition(), i))
		{
			spawnEnemyManager->SpawnEnemy(i);
		}
	}*/
}

void SceneGame::BGM_Update()
{
	//音量調整
	ChangeVolumeSoundMem(80, m_bgmHandle);
	//BGM
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP, false);
}

void SceneGame::SE_Update()
{
	//音量調整
	ChangeVolumeSoundMem(150, m_seHandle);
	//BGM
	
	PlaySoundMem(m_seHandle, DX_PLAYTYPE_LOOP, false);
}

void SceneGame::QuestionSelectUpdate(int _nextSectionNumber)
{
	m_Ui->m_select->DownSelect(nowSelectWepon, eSelectWepon_Num, m_Idm->joyPad->isDDOWN == true);
	m_Ui->m_select->UpSelect(nowSelectWepon, eSelectWepon_Num, m_Idm->joyPad->isDUP == true);

	switch (nowSelectWepon)
	{
	case eSelectWepon_YES:
		selectWeponPointPos.y = selectWeponYesPos.y;
		break;
	case eSelectWepon_NO:
		selectWeponPointPos.y = selectWeponNoPos.y;
		break;
	}


	if (m_Idm->joyPad->isB == true)
	{
		switch (nowSelectWepon)
		{
		case eSelectWepon_YES:
			m_tutorialSectionNumber = _nextSectionNumber;
			m_sectionTime = 0;
			m_fadeAlpha = 0;

			if (m_isSection_2LeftBoxEvent == true)
			{
				m_SelectWeponMyPower = 1;
				m_isSection_3LeftBoxEvent = false;
				m_isSection_3RightBoxEvent = false;
				m_isSection_3FowerdBoxEvent = false;
				m_isSection_2SelectFlag = true;
			}
			if (m_isSection_2RightBoxEvent == true)
			{
				m_SelectWeponMyPower = 2;
				m_isSection_3LeftBoxEvent = false;
				m_isSection_3RightBoxEvent = false;
				m_isSection_3FowerdBoxEvent = false;
				m_isSection_2SelectFlag = true;
			}
			if (m_isSection_2FowerdBoxEvent == true)
			{
				m_SelectWeponMyPower = 3;
				m_isSection_3LeftBoxEvent = false;
				m_isSection_3RightBoxEvent = false;
				m_isSection_3FowerdBoxEvent = false;
				m_isSection_2SelectFlag = true;
			}

			if (m_tutorialSectionNumber == 3)
			{
				if (m_isSection_3LeftBoxEvent == true)
				{
					m_SelectWeponGivPower = 1;
				}
				if (m_isSection_3RightBoxEvent == true)
				{
					m_SelectWeponGivPower = 2;

				}
				if (m_isSection_3FowerdBoxEvent == true)
				{
					m_SelectWeponGivPower = 3;
				}

				if (m_isSection_3SelectFlag == true)
				{
					m_isSection_3FinalAnser = true;
				}
			}
		
			break;
			case eSelectWepon_NO:
			m_player->SetPosition(VGet(0, 100, 0));
			
			if (m_tutorialSectionNumber == 2)
			{
				m_isSection_2SelectFlag = false;
				if (m_isSection_2FowerdBoxEvent == true)
				{
					m_isSection_2FowerdBoxEvent = false;
				}
				if (m_isSection_2LeftBoxEvent == true)
				{
					m_isSection_2LeftBoxEvent = false;
				}
				if (m_isSection_2RightBoxEvent == true)
				{
					m_isSection_2RightBoxEvent = false;
				}
			}

			break;
		}
	}
}

void SceneGame::QuestionSelectDraw()
{
	DrawGraph(0, 0, m_Section2GraphHandle[4], true);
	DrawGraph(0, 0, m_Section2GraphHandle[5], true);
	DrawGraph(selectWeponPointPos.x - 100, selectWeponPointPos.y - 190, m_Section2GraphHandle[6], true);

#ifdef _DEBUG
	DrawString(selectWeponYesPos.x, selectWeponYesPos.y, "そうだ", 0xffffff);
	DrawString(selectWeponNoPos.x, selectWeponNoPos.y, "ちがう", 0xffffff);
	DrawFormatString(selectWeponPointPos.x, selectWeponPointPos.y, 0xff0000, "→");
#endif // _DEBUG

}

void SceneGame::QuestionSelectUpdate_2()
{
	m_Ui->m_select->DownSelect(nowSelectWepon, eSelectWepon_Num, m_Idm->joyPad->isDDOWN == true);
	m_Ui->m_select->UpSelect(nowSelectWepon, eSelectWepon_Num, m_Idm->joyPad->isDUP == true);

	switch (nowSelectWepon)
	{
	case eSelectWepon_YES:
		selectWeponPointPos.y = selectWeponYesPos.y;
		break;
	case eSelectWepon_NO:
		selectWeponPointPos.y = selectWeponNoPos.y;
		break;
	}


	if (m_Idm->joyPad->isB == true)
	{
		switch (nowSelectWepon)
		{
		case eSelectWepon_YES:

			if (m_tutorialSectionNumber == 3)
			{
				if (m_isSection_3LeftBoxEvent == true)
				{
					m_SelectWeponGivPower = 1;
				}
				if (m_isSection_3RightBoxEvent == true)
				{
					m_SelectWeponGivPower = 2;

				}
				if (m_isSection_3FowerdBoxEvent == true)
				{
					m_SelectWeponGivPower = 3;
				}

				m_isSection_3FinalAnser = true;
				
			}

			break;
		case eSelectWepon_NO:
			

			break;
		}
	}
}

void SceneGame::QuestionSelectDraw_2()
{
	DrawGraph(0, 0, m_Section3GraphHandle[0], true);
	DrawGraph(0, 0, m_Section2GraphHandle[5], true);
	DrawGraph(selectWeponPointPos.x - 100, selectWeponPointPos.y - 190, m_Section2GraphHandle[6], true);
}


//=========================================================//
/*デバック*/
//=========================================================//
void SceneGame::DebugInit()
{
	m_player.get()->Init();
	
	m_enemyDoragon->Init();
	m_enemyFox->Init();

	m_camera.get()->Init();

	m_mapTutorial.get()->Init();
	m_skyDome.get()->Init();

	m_light.get()->Init();

	m_command->Init();
	PolygonInit();
}

void SceneGame::DebugUpdate()
{
	//カメラの処理
	m_camera.get()->SetTag("controlCamera");//カメラのタグの設定
	m_camera.get()->SetTarget(m_player->GetPosition());//ターゲットの設定
	m_camera.get()->Update();//更新
	

	m_player.get()->Update(m_camera->GetHAngle(), m_camera->GetSinParam(), m_camera->GetCosParam());

	m_enemyFox->Update(m_player->GetPosition());
	m_enemyFox->SetTag("section4");

	if (m_collision->CheckSphereHitCollision(m_player->GetPosition(), m_player->GetRadius(), m_enemyFox->GetPosition(), m_enemyFox->GetDamageDistance()))
	{
		if (m_player->GetIsAttack() == true)
		{
			m_enemyFox->TakeDamage(10);
		}
	}
	//m_enemyDoragon->Update();

	m_mapTutorial.get()->Update();
	m_skyDome.get()->Update();

	m_light.get()->Update();

	m_command->Update();

	PolygoUpdate(m_mapTutorial->GetModelHandle());
}

void SceneGame::DebugDraw()
{
	m_camera.get()->Draw();

	m_player.get()->Draw();

	m_enemyFox->Draw();
	//m_enemyDoragon->Draw();

	m_mapTutorial.get()->Draw();
	m_skyDome.get()->Draw();

	m_light.get()->Draw();
	
	m_command->Draw();
	DrawFormatString(800, 20, 0xffffff, "FPS:%f", GetFPS());
}

void SceneGame::DebugFinal()
{
	m_player.get()->Final();
	
	m_enemyFox->Final();
	m_enemyDoragon->Final();

	m_camera.get()->Final();

	m_mapTutorial.get()->Final();
	m_skyDome.get()->Final();

	m_command->Final();
	m_light.get()->Final();

}
//=========================================================//
/*デバック*/
//=========================================================//


void SceneGame::TutorialResous()
{
	/*セクション１の画像*/
	m_Section1GraphHandle[0] = LoadGraph("../Asset/2D/Tutorial/Section1/TutorialEventScene_Section_1.png");
	m_Section1GraphHandle[1] = LoadGraph("../Asset/2D/Tutorial/Section1/TutorialMoveSection_1.png");
	/*セクション２の画像*/
	m_Section2GraphHandle[0] = LoadGraph("../Asset/2D/Tutorial/Section2/TutorialJumpSection_2.png");
	m_Section2GraphHandle[1] = LoadGraph("../Asset/2D/Tutorial/Section2/TutorialSection_2_LeftWeponSelect.png");
	m_Section2GraphHandle[2] = LoadGraph("../Asset/2D/Tutorial/Section2/TutorialSection_2_FowerdWeponSelect.png");
	m_Section2GraphHandle[3] = LoadGraph("../Asset/2D/Tutorial/Section2/TutorialSection_2_RightWeponSelect.png");
	m_Section2GraphHandle[4] = LoadGraph("../Asset/2D/Tutorial/Section2/TutorialSection_2_WeponSelect.png");
	m_Section2GraphHandle[5] = LoadGraph("../Asset/2D/Tutorial/Section2/TutorialSection_2_QuestionWeponSelectBackGround.png");
	m_Section2GraphHandle[6] = LoadGraph("../Asset/2D/Tutorial/Section2/SelectPoint.png");


	/*セクション3の画像*/
	m_Section3GraphHandle[0] = LoadGraph("../Asset/2D/Tutorial/Section3/selectWeponPowerGiv.png");
	m_Section3GraphHandle[1] = LoadGraph("../Asset/2D/Tutorial/Section3/selectWeponPowerGiv_2.png");
	m_Section3GraphHandle[2] = LoadGraph("../Asset/2D/Tutorial/Section3/FowerdfalseGraph.png");
	m_Section3GraphHandle[3] = LoadGraph("../Asset/2D/Tutorial/Section3/LeftfalseGraph.png");
	m_Section3GraphHandle[4] = LoadGraph("../Asset/2D/Tutorial/Section3/RighitfalseGraph.png");
	m_Section3GraphHandle[5] = LoadGraph("../Asset/2D/Tutorial/Section3/FowerdTrueGraph.png");
	m_Section3GraphHandle[6] = LoadGraph("../Asset/2D/Tutorial/Section3/LeftTrueGraph.png");
	m_Section3GraphHandle[7] = LoadGraph("../Asset/2D/Tutorial/Section3/RightTrueGraph.png");
	m_Section3GraphHandle[8] = LoadGraph("../Asset/2D/Tutorial/Section3/FinalAnserSelctWepon.png");
	m_Section3GraphHandle[8] = LoadGraph("../Asset/2D/Tutorial/Section3/FinalAnserSelectBackGround.png");


	/*セクション4の画像*/
	m_Section4GraphHandle[0] = LoadGraph("../Asset/2D/Tutorial/Section4/Tutorial_Section4_WeponGetEventBackGround.png");
	m_Section4GraphHandle[1] = LoadGraph("../Asset/2D/Tutorial/Section4/GetWeponSorwd.png");
	m_Section4GraphHandle[2] = LoadGraph("../Asset/2D/Tutorial/Section4/GetWeponShield.png");
	m_Section4GraphHandle[3] = LoadGraph("../Asset/2D/Tutorial/Section4/GetWeponRod.png");
	m_Section4GraphHandle[4] = LoadGraph("../Asset/2D/Tutorial/Section4/NEXTPushB.png");
	m_Section4GraphHandle[5] = LoadGraph("../Asset/2D/Tutorial/Section4/SavePointKaisetu.png");
	m_Section4GraphHandle[6] = LoadGraph("../Asset/2D/Tutorial/Section4/CloseSavePointKaisetu.png");
	m_Section4GraphHandle[7] = LoadGraph("../Asset/2D/Tutorial/Section4/SectionChangeText.png");
	m_Section4GraphHandle[8] = LoadGraph("../Asset/2D/Command/actionCommand.png");






	/*セクション5の画像*/
	m_Section5GraphHandle[0] = LoadGraph("../Asset/2D/Tutorial/TutorialEventScene_Section_1.png");
	m_Section5GraphHandle[1] = LoadGraph("../Asset/2D/Tutorial/TutorialMoveSection_1.png");

}

//=========================================================//
/*チュートリアル*/
//=========================================================//
void SceneGame::TutorialInit()
{
	/*スポーン地点の初期化*/
	/*spawnEnemyManager->AddSpawnPoint(VGet(0.0f, 150.0f, 700.0f));
	spawnEnemyManager->Init();*/

	//m_tutorialSectionNumber = 4;

	m_tutorialSectionNumber = 1;


	m_player.get()->Init();
	m_enemyFox->Init();
	
	m_tsSword.get()->Init();
	m_tsShield.get()->Init();
	m_tsRod.get()->Init();
	m_camera.get()->Init();
	m_mapTutorial.get()->Init();
	m_skyDome.get()->Init();
	m_light.get()->Init();
	m_command.get()->Init();
	PolygonInit();

	m_effect.get()->Init();

	m_nextSectionPosition = VGet(0, 50, 700);
	m_nextSectionRadius = 200.0f;
}

void SceneGame::TutorialUpdate()
{
	BGM_Update();
	if (m_player->GetIsGround() && !m_player->GetIsGround())
	{
		SE_Update();
	}


	if (m_player->GetIsMove() == true && m_player->GetIsGround() == true)
	{
		SE_Update();
	}
	else
	{
		StopSoundMem(m_seHandle);
	}


	PolygoUpdate(m_mapTutorial->GetModelHandle());

	if (m_tutorialSectionNumber == 5)
	{
	}
	if (m_tutorialSectionNumber == 4)
	{
		if (m_section_4EventTime >= m_section_4EventMaxTime)
		{
			m_section_4EventTime = m_section_4EventMaxTime;//イベント終了
			
			if (m_section_4EventTime_2 >= m_section_4EventMaxTime_2)
			{
				//セーブポイントの説明イベント
				if (m_isSavePointEvent == true)
				{
					//イベント中に２００秒経過したら
					if (m_savePointEventPushBottonTime >= 10.0f)
					{
						//ボタンを押してイベントを終える
						if (m_Idm->joyPad->isB == true && m_savePointEventPushBottonTime <= 100.0f)
						{
							m_isSavePointEvent = false;
						}
					}
					else
					{
						m_savePointEventPushBottonTime++;
					}

				}
				else//イベント終了
				{
					if (m_savePointCount == 0)
					{
						m_camera.get()->SetTag("controlCamera");//カメラのタグの設定
						m_camera.get()->SetTarget(m_player->GetPosition());//ターゲットの設定
						m_camera.get()->Update();//更新
						m_player.get()->Update(m_camera->GetHAngle(), m_camera->GetSinParam(), m_camera->GetCosParam());
						m_effect->SetTag("SavePoint");
						m_command->Update();
						if (m_collision->CheckSphereHitCollision(m_player->GetPosition(), m_player->GetRadius(), m_savePoint->GetPosition(), 30.0f))
						{
							if (m_Idm->joyPad->isY == true)
							{
								isSavePoint = true;
								m_savePoint->SetIsSaving(true);
							}
							//DrawString(0, 0, "Save?", 0xffffff);
						}

					}

					if (m_savePointCount == 1)
					{
						
							m_camera.get()->SetTag("controlCamera");//カメラのタグの設定
							m_camera.get()->SetTarget(m_player->GetPosition());//ターゲットの設定
							m_camera.get()->Update();//更新
							m_player.get()->Update(m_camera->GetHAngle(), m_camera->GetSinParam(), m_camera->GetCosParam());

							/*ぶきを持たせる*/
							m_tsSword->SetTag("playerAttachWeponTS_Sword");
							m_tsSword->SetAttachCharacterModel(m_player->GetModelHandle());
							m_tsSword->SetPosition(m_player->GetRightHandPosition());
							m_tsSword->SetAngle(m_player->GetAngle());
							m_tsSword->SetAttachCharacterRightHandPos(m_player->GetRightHandPosition());

							m_command->Update();
							
							m_effect->SetTag("SavePoint");
							if (m_collision->CheckSphereHitCollision(m_player->GetPosition(), m_player->GetRadius(), m_savePoint->GetPosition(), 30.0f))
							{
								if (m_Idm->joyPad->isY == true)
								{
									isSavePoint = true;
									m_savePoint->SetIsSaving(true);
								}
								//DrawString(0, 0, "Save?", 0xffffff);
							}
							/*if (m_collision->CheckSphereHitCollision(m_player->GetPosition(), m_player->GetRadius(), m_enemyFox->GetPosition(), m_enemyFox->GetDamageDistance()))
							{
								if (m_command->GetIsAttackCommand() == true)
								{
									m_enemyFox->TakeDamage(10);
								}
							}*/
							m_enemyFox->Update(m_player->GetPosition());
					}

				}
			}
			else
			{
				

				m_section_4EventTime_2++;
				m_isSavePointEvent = true;
				m_player->SetIsAnim(4);
				m_player->SetIsMove(false);
				m_player->GetAnimUpdate();
				m_camera->SetTag("Section_4EventCamera_1");
				m_camera->SetTarget(VGet(700, 2.0f, 700.0f));
				m_camera.get()->Update();
				
				m_mapTutorial->SetIsSection_2(true);

				m_light->SetTag("normal");

				m_effect->SetTag("SavePoint");
			}
		}
		else
		{
			if (m_Idm->joyPad->isB == true)
			{
				m_section_4EventTime = m_section_4EventMaxTime;
				
			}
			m_section_4EventTime++;//イベント再生
			
			m_player->SetPosition(VGet(0, 100, 0));
			m_player.get()->Update(m_camera->GetHAngle(), m_camera->GetSinParam(), m_camera->GetCosParam());
			

			m_light->SetTag("normal");
			if (m_fadeAlpha_Section4_1 >= 255)
			{
				m_fadeAlpha_Section4_1 = 255;
			

			}
			else
			{
				m_fadeAlpha_Section4_1 += 1.0f;
			}
		}

	
		m_light->SetTag("normal");
		m_mapTutorial->SetIsSection_4(true);
	}
	if (m_tutorialSectionNumber == 3)
	{
		if (m_section_3Time >= m_section_3MaxTime)
		{
			m_section_3Time = m_section_3MaxTime;

			if (m_isSection_3FinalAnser == true)
			{
				if (m_fadeAlpha_1 >= 255 + 150)
				{
					m_fadeAlpha_1 = 255 + 150;

					m_camera->SetPosition(VGet(0, 150, 0));
					m_camera->Update();
					m_tutorialSectionNumber = 4;
				}
				else
				{
					m_fadeAlpha_2 += 0.8f;
				}

				if (m_fadeAlpha_2 >= 255 + 150)
				{
					m_fadeAlpha_2 = 255 + 150;
					m_tutorialSectionNumber = 4;
				}
				else
				{
					m_fadeAlpha_2 += 0.8f;
				}

			}

			if (m_SelectWeponMyPower != 1 && m_isSection_3LeftBoxEvent == true)
			{
				m_light->SetTag("section_2LeftWeponSelectEvent");
				m_player->SetIsAnim(4);
				m_player->SetIsMove(false);
				m_player.get()->SetPosition(VGet(m_player->GetPosition().x, m_LeftBox.m_position.y + 130.0f, m_player->GetPosition().z));
				m_player->GetAnimUpdate();
				m_camera->SetTag("Section_2EventCameraLeftWeponSelectCamera");
				m_camera->SetTarget(VAdd(m_player->GetPosition(), VGet(0, 100, 0)));
				m_camera->Update();
				m_effect->SetTag("AllStopEffect");

				m_tsSword->SetTag("nowSelectSword");
				if (m_fadeAlpha >= 255 + 150)
				{
					QuestionSelectUpdate_2();//武器選択
				}
			}

			if (m_SelectWeponMyPower != 2 && m_isSection_3RightBoxEvent == true)
			{
				m_light->SetTag("section_2LeftWeponSelectEvent");
				m_player->SetIsAnim(4);
				m_player->SetIsMove(false);
				m_player.get()->SetPosition(VGet(m_player->GetPosition().x, m_LeftBox.m_position.y + 130.0f, m_player->GetPosition().z));
				m_player->GetAnimUpdate();
				m_camera->SetTag("Section_2EventCameraRightWeponSelectCamera");
				m_camera->SetTarget(VAdd(m_player->GetPosition(), VGet(0, 100, 0)));
				m_camera->Update();

				m_tsShield->SetTag("nowSelectShield");
				if (m_fadeAlpha >= 255 + 150)
				{
					QuestionSelectUpdate_2();//武器選択
				}
			}

			if (m_SelectWeponMyPower != 3 && m_isSection_3FowerdBoxEvent == true)
			{
				m_light->SetTag("section_2LeftWeponSelectEvent");
				m_player->SetIsAnim(4);
				m_player->SetIsMove(false);
				m_player.get()->SetPosition(VGet(m_player->GetPosition().x, m_LeftBox.m_position.y + 130.0f, m_player->GetPosition().z));
				m_player->GetAnimUpdate();
				m_camera->SetTag("Section_2EventCameraFowerdWeponSelectCamera");
				m_camera->SetTarget(VAdd(m_player->GetPosition(), VGet(0, 100, 0)));
				m_camera->Update();

				m_tsRod->SetTag("nowSelectRod");
				if (m_fadeAlpha >= 255 + 150)
				{
					QuestionSelectUpdate_2();//武器選択
				}
			}
			if (m_isSection_3FowerdBoxEvent == false &&
				m_isSection_3LeftBoxEvent == false &&
				m_isSection_3RightBoxEvent == false)
			{

				m_command.get()->Update();
				m_camera.get()->SetTag("controlCamera");//カメラのタグの設定
				m_camera.get()->SetTarget(m_player->GetPosition());//ターゲットの設定
				m_camera.get()->Update();//更新
				m_player.get()->Update(m_camera->GetHAngle(), m_camera->GetSinParam(), m_camera->GetCosParam());

				m_light->SetTag("normal");

				Section3Collision();
				m_fadeAlpha = 0;
			}
		}
		else
		{

			m_section_3Time++;
			//カメラの処理
			m_player->SetIsAnim(4);
			m_player->SetIsMove(false);
			if (m_SelectWeponMyPower == 1)
			{
				m_player.get()->SetPosition(VGet(m_player->GetPosition().x, m_LeftBox.m_position.y + 180.0f, m_player->GetPosition().z));
				m_camera->SetTag("Section_3EventCamera1");
				m_camera.get()->SetTarget(m_nextSectionPosition);
				m_camera->Update();
			}
			if (m_SelectWeponMyPower == 2)
			{
				m_player.get()->SetPosition(VGet(m_player->GetPosition().x , m_RightBox.m_position.y + 180.0f, m_player->GetPosition().z));
				m_camera->SetTag("Section_3EventCamera2");
				m_camera.get()->SetTarget(m_nextSectionPosition);
				m_camera->Update();
			}
			if (m_SelectWeponMyPower == 3)
			{
				m_player.get()->SetPosition(VGet(m_player->GetPosition().x , m_FowerdBox.m_position.y + 180.0f, m_player->GetPosition().z));
				m_camera->SetTag("Section_3EventCamera3");
				m_camera.get()->SetTarget(m_nextSectionPosition);
				m_camera->Update();
			}
			m_player->GetAnimUpdate();
			//m_mapTutorial->SetIsSection_2(true);
		}


		if (m_fadeAlpha >= 255 + 150)
		{
			m_fadeAlpha = 255 + 150;
			if (m_sectionTime >= m_sectionMaxTime)
			{
				m_sectionTime = m_sectionMaxTime;
			}
			else
			{
				m_sectionTime += 1.0f;
			}
		}
		else
		{
			m_fadeAlpha += 0.8f;
		}


	}
	if (m_tutorialSectionNumber == 2)
	{
		if (m_section_2Time >= m_section_2MaxTime)
		{
			m_section_2Time = m_section_2MaxTime;

			if (m_isSection_2LeftBoxEvent == true)
			{
				m_light->SetTag("section_2LeftWeponSelectEvent");
				m_player->SetIsAnim(4);
				m_player->SetIsMove(false);
				m_player.get()->SetPosition(VGet(m_player->GetPosition().x, m_LeftBox.m_position.y + 130.0f, m_player->GetPosition().z));
				m_player->GetAnimUpdate();
				m_camera->SetTag("Section_2EventCameraLeftWeponSelectCamera");
				m_camera->SetTarget(VAdd(m_player->GetPosition(), VGet(0,100,0)));
				m_camera->Update();
				m_effect->SetTag("AllStopEffect");

				m_tsSword->SetTag("nowSelectSword");
				if (m_fadeAlpha >= 255 + 150)
				{
					QuestionSelectUpdate(3);//武器選択
				}
			}

			if (m_isSection_2FowerdBoxEvent == true)
			{
				m_light->SetTag("section_2LeftWeponSelectEvent");
				m_player->SetIsAnim(4);
				m_player->SetIsMove(false);
				m_player.get()->SetPosition(VGet(m_player->GetPosition().x, m_LeftBox.m_position.y + 130.0f, m_player->GetPosition().z));
				m_player->GetAnimUpdate();
				m_camera->SetTag("Section_2EventCameraFowerdWeponSelectCamera");
				m_camera->SetTarget(VAdd(m_player->GetPosition(), VGet(0, 100, 0)));
				m_camera->Update();

				m_tsRod->SetTag("nowSelectRod");
				if (m_fadeAlpha >= 255 + 150)
				{
					QuestionSelectUpdate(3);//武器選択
				}

			}
			if (m_isSection_2RightBoxEvent == true)
			{
				m_light->SetTag("section_2LeftWeponSelectEvent");
				m_player->SetIsAnim(4);
				m_player->SetIsMove(false);
				m_player.get()->SetPosition(VGet(m_player->GetPosition().x, m_LeftBox.m_position.y + 130.0f, m_player->GetPosition().z));
				m_player->GetAnimUpdate();
				m_camera->SetTag("Section_2EventCameraRightWeponSelectCamera");
				m_camera->SetTarget(VAdd(m_player->GetPosition(), VGet(0, 100, 0)));
				m_camera->Update();

				m_tsShield->SetTag("nowSelectShield");
				if (m_fadeAlpha >= 255 + 150)
				{
					QuestionSelectUpdate(3);//武器選択
				}
			}

			if (m_isSection_2FowerdBoxEvent == false &&
				m_isSection_2LeftBoxEvent == false &&
				m_isSection_2RightBoxEvent == false)
			{
				/*常時エフェクト*/
				m_effect.get()->SetTag("TutorialEffectSection_2LeftWeponSelect");
				

				m_tsSword->SetTag("nonSelectSword");
				m_tsSword.get()->SetPosition(VAdd(m_LeftBox.m_position, VGet(0,160,0)));
				
				
				m_tsShield->SetTag("nonSelectShield");
				m_tsShield.get()->SetPosition(VAdd(m_RightBox.m_position, VGet(0, 170, 0)));

				m_tsRod->SetTag("nonSelectRod");
				m_tsRod.get()->SetPosition(VAdd(m_FowerdBox.m_position, VGet(0, 120, 0)));

				//m_command.get()->Update();
				m_camera.get()->SetTag("controlCamera");//カメラのタグの設定
				m_camera.get()->SetTarget(m_player->GetPosition());//ターゲットの設定
				m_camera.get()->Update();//更新
				m_player.get()->Update(m_camera->GetHAngle(), m_camera->GetSinParam(), m_camera->GetCosParam());
			
				m_light->SetTag("normal");
				if (m_sectionTime >= m_sectionMaxTime)
				{
					m_sectionTime = m_sectionMaxTime;
				}
				else
				{
					m_sectionTime += 1.0f;
				}
				Section2Collision();
				m_fadeAlpha = 0;
			}
		}
		else
		{
			m_section_2Time++;
			//カメラの処理
			m_camera.get()->SetTag("Section_2EventCamera");
			if (m_section_2Time <= m_sectionMaxTime / 3)
			{
				m_camera.get()->SetTarget(m_LeftBox.m_position);//0番目左
			}
			if (m_section_2Time >= m_sectionMaxTime / 3 && m_section_2Time <= (m_sectionMaxTime / 3) * 2)
			{
				m_camera.get()->SetTarget(m_FowerdBox.m_position);//1番目正面
			}
			if (m_section_2Time >= (m_sectionMaxTime / 3) * 2 && m_section_2Time <= m_sectionMaxTime)
			{
				m_camera.get()->SetTarget(m_RightBox.m_position);//２番目→
			}
			m_camera.get()->Update();
			m_mapTutorial->SetIsSection_2(true);
		}

		if (m_fadeAlpha >= 255 + 150)
		{
			m_fadeAlpha = 255 + 150;
			if (m_sectionTime >= m_sectionMaxTime)
			{
				m_sectionTime = m_sectionMaxTime;
			}
			else
			{
				m_sectionTime += 1.0f;
			}
		}
		else
		{
			m_fadeAlpha += 0.8f;
		}
		
	}
	if (m_tutorialSectionNumber == 1)
	{
		m_mapTutorial->SetIsSection_2(false);

		if (m_fadeAlpha >= 255)
		{
			m_fadeAlpha = 255;

			if (m_sectionTime >= m_sectionMaxTime)
			{
				m_sectionTime = m_sectionMaxTime;
			}
			else
			{
				m_sectionTime += 1.0f;
			}
		}
		else
		{
			m_fadeAlpha += 0.8f;
		}

		if (m_fadeAlpha >= 255)
		{
			m_camera.get()->SetTag("controlCamera");//カメラのタグの設定
			m_camera.get()->SetTarget(m_player->GetPosition());//ターゲットの設定
			m_camera.get()->Update();//更新
			m_player.get()->Update(m_camera->GetHAngle(), m_camera->GetSinParam(), m_camera->GetCosParam());
		}
		else
		{
			//カメラの処理
			m_camera.get()->SetTag("Section_1EventCamera");
			m_camera.get()->SetTarget(m_nextSectionPosition);
			m_camera.get()->Update();
		}


		if (m_collision->CheckSphereHitCollision(m_player->GetPosition(), m_player->GetRadius(), m_nextSectionPosition, m_nextSectionRadius) == true)
		{
			m_tutorialSectionNumber = 2;
			m_sectionTime = 0;
		}

		
		m_light.get()->SetTag("normal");
		m_effect.get()->SetTag("TutorialEffectSection_1");
	}
	
	
	m_skyDome.get()->Update();
	m_light.get()->Update();
	m_mapTutorial.get()->Update();
	m_tsSword.get()->Update();
	m_tsShield.get()->Update();
	m_tsRod.get()->Update();
	m_effect.get()->Update();
	//攻撃コマンドのフラグをプレイヤーに渡す
	m_player.get()->SetIsAttackCommand(m_command->GetIsAttackCommand());
	
}

void SceneGame::TutorialDraw()
{
	m_camera.get()->Draw();
	m_player.get()->Draw();
	m_enemyFox->Draw();
	m_mapTutorial->Draw();
	m_skyDome.get()->Draw();
	m_light.get()->Draw();
	

	if (m_tutorialSectionNumber == 5)
	{
	}
	if (m_tutorialSectionNumber == 4)
	{
		if (m_section_4EventTime_2 >= m_section_4EventMaxTime_2)
		{
			//セーブポイントの説明イベント
			if (m_isSavePointEvent == true)
			{
				//イベント中に２００秒経過したら
				if (m_savePointEventPushBottonTime >= 10.0f)
				{
					DrawGraph(0, 0, m_Section4GraphHandle[5], true);
				
					if (m_savePointEventPushBottonTime <= 100.0f)
					{
						DrawGraph(0, 0, m_Section4GraphHandle[6], true);
					}
				}
				else
				{
					
				}

			}
			else//イベント終了
			{
				if (m_savePointCount == 0)
				{
					m_effect->Draw();
					if (m_collision->CheckSphereHitCollision(m_player->GetPosition(), m_player->GetRadius(), m_savePoint->GetPosition(), 30.0f))
					{
						DrawGraph(20, 420, m_Section4GraphHandle[8], true);
					}
					m_command->Draw();

				}
				if (m_savePointCount == 1)
				{
					m_effect->Draw();
					m_tsSword->Draw();
					m_enemyFox->SetTag("section4");
					
					if (m_collision->CheckSphereHitCollision(m_player->GetPosition(), m_player->GetRadius(), m_enemyFox->GetPosition(), m_enemyFox->GetDamageDistance()))
					{
						if (m_player->GetIsAttack() == true)
						{
							m_enemyFox->TakeDamage(10);
						}
					}

					if (m_collision->CheckSphereHitCollision(m_player->GetPosition(), m_player->GetRadius(), m_savePoint->GetPosition(), 30.0f))
					{
						DrawGraph(20, 420, m_Section4GraphHandle[8], true);
					}
					m_command->Draw();
				}

			}
		}
		else
		{
			m_effect->Draw();
		}

		if (m_section_4EventTime <= m_section_4EventMaxTime - 1)
		{

			if (m_fadeAlpha_Section4_1 <= 255)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha_Section4_1);
				DrawGraph(0, 0, m_Section4GraphHandle[0], true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

				if (m_SelectWeponMyPower == 1)
				{
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha_Section4_1);
					DrawGraph(0, 0, m_Section4GraphHandle[1], true);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}

				if (m_SelectWeponMyPower == 2)
				{
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha_Section4_1);
					DrawGraph(0, 0, m_Section4GraphHandle[2], true);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}

				if (m_SelectWeponMyPower == 3)
				{
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha_Section4_1);
					DrawGraph(0, 0, m_Section4GraphHandle[3], true);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}

				if (m_section_4EventTime >= 300)
				{
					DrawGraph(0, 0, m_Section4GraphHandle[4], true);
				}

			}
		}


	}
	if (m_tutorialSectionNumber == 3)
	{
		m_mapTutorial->SetTag("Foundation");
		

		if (m_section_3Time < m_section_3MaxTime && m_section_3Time > 2)
		{
			
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
			DrawGraph(0, 0, m_Section3GraphHandle[1], true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		
		/*m_effect.get()->Draw();*/

		if (m_SelectWeponMyPower != 1)
		{
			m_tsSword.get()->Draw();//剣
		}
		if (m_SelectWeponMyPower != 2)
		{
			m_tsShield.get()->Draw();
		}
		if (m_SelectWeponMyPower != 3)
		{
			m_tsRod.get()->Draw();
		}

		if (m_isSection_3FinalAnser == true && m_fadeAlpha_2 <= 255 + 150)
		{
			if (m_SelectWeponMyPower == 1)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha_2);
				DrawGraph(0, 0, m_Section3GraphHandle[6], true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			if (m_SelectWeponMyPower == 2)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha_2);
				DrawGraph(0, 0, m_Section3GraphHandle[7], true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			if (m_SelectWeponMyPower == 3)
			{
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha_2);
					DrawGraph(0, 0, m_Section3GraphHandle[5], true);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}

			if (m_SelectWeponGivPower == 1)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha_2);
				DrawGraph(0, 100, m_Section3GraphHandle[3], true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			if (m_SelectWeponGivPower == 2)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha_2);
				DrawGraph(0, 100, m_Section3GraphHandle[4], true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			if (m_SelectWeponGivPower == 3)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha_2);
				DrawGraph(0, 100, m_Section3GraphHandle[2], true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}


		}
		
		if(m_isSection_3FinalAnser == false)
		{
			if (m_SelectWeponMyPower != 1 && m_isSection_3LeftBoxEvent == true)
			{
				if (m_fadeAlpha < 255 + 150)
				{
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
					DrawGraph(0, 0, m_Section2GraphHandle[1], true);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}
				else
				{
					QuestionSelectDraw_2();
				}
			}
			if (m_SelectWeponMyPower != 3 && m_isSection_3FowerdBoxEvent == true)
			{
				if (m_fadeAlpha < 255 + 150)
				{
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
					DrawGraph(0, 0, m_Section2GraphHandle[2], true);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}
				else
				{
					QuestionSelectDraw_2();
				}
			}
			if (m_SelectWeponMyPower != 2 && m_isSection_3RightBoxEvent == true)
			{
				

				if (m_fadeAlpha < 255 + 150)
				{
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
					DrawGraph(0, 0, m_Section2GraphHandle[3], true);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}
				else
				{
					QuestionSelectDraw_2();
				}
			}
		}
		
	}
	if (m_tutorialSectionNumber == 2)
	{
		m_mapTutorial->SetTag("Foundation");
		

		if (m_sectionTime < m_sectionMaxTime && m_sectionTime > 2)
		{
			DrawGraph(0, 0, m_Section2GraphHandle[0], true);
		}

		
	
		m_effect.get()->Draw();
		m_tsSword.get()->Draw();//剣
		m_tsShield.get()->Draw();
		m_tsRod.get()->Draw();

		

		if (m_isSection_2LeftBoxEvent == true)
		{
			if (m_fadeAlpha < 255 + 150)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
				DrawGraph(0, 0, m_Section2GraphHandle[1], true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else
			{
				QuestionSelectDraw();
			}
		}
		if (m_isSection_2FowerdBoxEvent == true)
		{
			if (m_fadeAlpha < 255 + 150)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
				DrawGraph(0, 0, m_Section2GraphHandle[2], true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else
			{
				QuestionSelectDraw();
			}
		}
		if (m_isSection_2RightBoxEvent == true)
		{
			if (m_fadeAlpha < 255 + 150)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
				DrawGraph(0, 0, m_Section2GraphHandle[3], true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else
			{
				QuestionSelectDraw();
			}
		}


	}
	if (m_tutorialSectionNumber == 1)
	{

		m_effect.get()->Draw();

		if (m_isSectionSkip == false)
		{
			if (m_sectionTime < m_sectionMaxTime && m_sectionTime > 2)
			{
				DrawGraph(0, 0, m_Section1GraphHandle[1], true);
			}

			if (m_fadeAlpha < 255)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
				DrawGraph(0, 0, m_Section1GraphHandle[0], true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}

	

#ifdef _DEBUG
	DrawSphere3D(m_nextSectionPosition, m_nextSectionRadius, 5, 0xffffff, 0xffffff, false);
#endif // _DEBUG
	//m_command.get()->Draw();
	
}

void SceneGame::TutorialFinal()
{
	m_tutorialSectionNumber = 0;

	m_player.get()->Final();
	
	m_tsSword.get()->Final();
	m_camera.get()->Final();
	m_mapTutorial.get()->Final();
	m_skyDome.get()->Final();
	m_light.get()->Final();
	m_effect.get()->Final();
	m_command.get()->Final();

	/*spawnEnemyManager->ResetEnemies();
	spawnEnemyManager->Final();*/
	for (int i = 0; i < 7; i++)
	{
		DeleteGraph(m_Section2GraphHandle[i]);
	}
}
void SceneGame::Section2Collision()
{
	/*土台の当たり判定*/
	/*if (m_collision->CheckBoxHitCollision(m_player->GetPosition(), m_player->GetRadius(), m_LeftBox.m_position, m_LeftBox.m_size) == true)
	{
		m_player->SetPosition(m_collision->CheckBoxResolveCollision(m_player->GetPosition(), m_player->GetRadius(), m_LeftBox.m_position, m_LeftBox.m_size));
	}
	if (m_collision->CheckBoxHitCollision(m_player->GetPosition(), m_player->GetRadius(), m_RightBox.m_position, m_RightBox.m_size))
	{
		m_player->SetPosition(m_collision->CheckBoxResolveCollision(m_player->GetPosition(), m_player->GetRadius(), m_RightBox.m_position, m_RightBox.m_size));
	}
	if (m_collision->CheckBoxHitCollision(m_player->GetPosition(), m_player->GetRadius(), m_FowerdBox.m_position, m_FowerdBox.m_size))
	{
		m_player->SetPosition(m_collision->CheckBoxResolveCollision(m_player->GetPosition(), m_player->GetRadius(), m_FowerdBox.m_position, m_FowerdBox.m_size));
	}*/
	PolygoUpdate(m_mapTutorial->GetFoundationModelHandle_0());
	PolygoUpdate(m_mapTutorial->GetFoundationModelHandle_1());
	PolygoUpdate(m_mapTutorial->GetFoundationModelHandle_2());


	/*イベントフラグの当たり判定*/
	if (m_collision->CheckSphereHitCollision(m_player->GetPosition(), m_player->GetRadius(), VGet(m_LeftBox.m_position.x, m_LeftBox.m_position.y + 150.0f, m_LeftBox.m_position.z), 10.0f))
	{
		if (m_section_2EventTime >= m_section_2EventMaxTime)
		{
			m_section_2EventTime = m_section_2EventMaxTime;
			m_isSection_2LeftBoxEvent = true;
		}
		else
		{
			m_section_2EventTime++;
		}
	}

	/*イベントフラグの当たり判定*/
	if (m_collision->CheckSphereHitCollision(m_player->GetPosition(), m_player->GetRadius(), VGet(m_RightBox.m_position.x, m_RightBox.m_position.y + 100.0f, m_RightBox.m_position.z), 10.0f))
	{
		if (m_section_2EventTime >= m_section_2EventMaxTime)
		{
			m_section_2EventTime = m_section_2EventMaxTime;
			m_isSection_2RightBoxEvent = true;
		}
		else
		{
			m_section_2EventTime++;
		}
	}

	/*イベントフラグの当たり判定*/
	if (m_collision->CheckSphereHitCollision(m_player->GetPosition(), m_player->GetRadius(), VGet(m_FowerdBox.m_position.x, m_FowerdBox.m_position.y + 110.0f, m_FowerdBox.m_position.z), 10.0f))
	{
		if (m_section_2EventTime >= m_section_2EventMaxTime)
		{
			m_section_2EventTime = m_section_2EventMaxTime;
			m_isSection_2FowerdBoxEvent = true;
		}
		else
		{
			m_section_2EventTime++;
		}
	}

}
void SceneGame::Section3Collision()
{
	/*土台の当たり判定*/
	/*if ( m_collision->CheckBoxHitCollision(m_player->GetPosition(), m_player->GetRadius(), m_LeftBox.m_position, m_LeftBox.m_size))
	{
		m_player->SetIsGround(true);
		m_player->SetPosition(m_collision->CheckBoxResolveCollision(m_player->GetPosition(), m_player->GetRadius(), m_LeftBox.m_position, m_LeftBox.m_size));
	}
	if (m_collision->CheckBoxHitCollision(m_player->GetPosition(), m_player->GetRadius(), m_RightBox.m_position, m_RightBox.m_size))
	{
		m_player->SetIsGround(true);
		m_player->SetPosition(m_collision->CheckBoxResolveCollision(m_player->GetPosition(), m_player->GetRadius(), m_RightBox.m_position, m_RightBox.m_size));
	}
	if (m_collision->CheckBoxHitCollision(m_player->GetPosition(), m_player->GetRadius(), m_FowerdBox.m_position, m_FowerdBox.m_size))
	{
		m_player->SetIsGround(true);
		m_player->SetPosition(m_collision->CheckBoxResolveCollision(m_player->GetPosition(), m_player->GetRadius(), m_FowerdBox.m_position, m_FowerdBox.m_size));
	}*/
	PolygoUpdate(m_mapTutorial->GetFoundationModelHandle_0());
	PolygoUpdate(m_mapTutorial->GetFoundationModelHandle_1());
	PolygoUpdate(m_mapTutorial->GetFoundationModelHandle_2());


	/*イベントフラグの当たり判定*/
	if (m_SelectWeponMyPower != 1 && m_collision->CheckSphereHitCollision(m_player->GetPosition(), m_player->GetRadius(), VGet(m_LeftBox.m_position.x, m_LeftBox.m_position.y + 150.0f, m_LeftBox.m_position.z), 10.0f))
	{
		if (m_section_2EventTime >= m_section_2EventMaxTime)
		{
			m_section_2EventTime = m_section_2EventMaxTime;
			m_isSection_3LeftBoxEvent = true;
		}
		else
		{
			m_section_2EventTime++;
		}
	}

	/*イベントフラグの当たり判定*/
	if (m_SelectWeponMyPower != 2 && m_collision->CheckSphereHitCollision(m_player->GetPosition(), m_player->GetRadius(), VGet(m_RightBox.m_position.x, m_RightBox.m_position.y + 110.0f, m_RightBox.m_position.z), 10.0f))
	{
		if (m_section_2EventTime >= m_section_2EventMaxTime)
		{
			m_section_2EventTime = m_section_2EventMaxTime;
			m_isSection_3RightBoxEvent = true;
		}
		else
		{
			m_section_2EventTime++;
		}
	}

	/*イベントフラグの当たり判定*/
	if (m_SelectWeponMyPower != 3 && m_collision->CheckSphereHitCollision(m_player->GetPosition(), m_player->GetRadius(), VGet(m_FowerdBox.m_position.x, m_FowerdBox.m_position.y + 110.0f, m_FowerdBox.m_position.z), 10.0f))
	{
		if (m_section_2EventTime >= m_section_2EventMaxTime)
		{
			m_section_2EventTime = m_section_2EventMaxTime;
			m_isSection_3FowerdBoxEvent = true;
		}
		else
		{
			m_section_2EventTime++;
		}
	}


}
//=========================================================//
/*チュートリアル*/
//=========================================================//


//=========================================================//
/*SevenWondersTown*/
//=========================================================//
void SceneGame::SevenWondersTownInit()
{
}

void SceneGame::SevenWondersTownUpdate()
{
}

void SceneGame::SevenWondersTownDraw()
{
}

void SceneGame::SevenWondersTownFinal()
{
}
//=========================================================//
/*SevenWondersTown*/
//=========================================================//

