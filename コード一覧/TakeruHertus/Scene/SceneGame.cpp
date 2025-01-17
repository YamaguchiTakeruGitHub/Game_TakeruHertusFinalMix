#include "SceneGame.h"
#include "SceneManager.h"


SceneGame::SceneGame()
	: isStartButtonPressed(false)
	, m_isOpenMenu(false)
	, hp(100)
	, maxhp(100)
	, nextNode(VGet(0, 0, 0))

{
	m_path = std::make_shared<Path>();
	m_charaIcon = std::make_shared<CharacterIcon>();
	m_hpBar = std::make_shared<HPBar>();
	m_physics = std::make_shared<Physics>();
	m_player = std::make_shared<Player>();
	m_enemy1 = std::make_shared<EnemySmallFish>();
	m_enemy2 = std::make_shared<EnemyMidle>();
	m_enemy3 = std::make_shared<EnemyDinamic>();
	m_camera = std::make_shared<Camera>();

	m_ground = std::make_shared<Ground>();
	m_smallAricle = std::make_shared<SmallAricle>();
	
	m_skyDome = std::make_shared<SkyDome>();
	m_light = std::make_shared<LightManager>();
	m_gameMenu = std::make_shared<GameMenu>();
//	m_command = std::make_shared<Command>();

	m_onestavenue = std::make_shared<OneStAvenue>();
	m_meManager = std::make_shared<MapEventManager>();
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	m_Idm.get()->Init();
	m_gameMenu.get()->Init();
	m_hpBar.get()->Init();
	m_charaIcon.get()->Init();

	m_skyDome.get()->Init();
	m_ground.get()->Init();
	m_smallAricle.get()->Init();

	m_player.get()->Init(m_physics);
	m_enemy1.get()->Init(m_physics);
	m_enemy2.get()->Init(m_physics);
	m_enemy3.get()->Init(m_physics);
	m_camera.get()->Init();
	m_light.get()->Init();
	//m_command.get()->Init();

	isStartButtonPressed = false;
	m_isOpenMenu = false;

	hp = 1000;
	maxhp = 1000;
	nextNode = VGet(0, 0, 0);


	m_enemy1.get()->SetPath(m_path);

	/*ノードの開始地点*/
	/*m_path.get()->AddNode(VGet(0, 20, 0));
	m_path.get()->AddNode(VGet(0, 20, 100));
	m_path.get()->AddNode(VGet(0, 20, -100));
	m_path.get()->AddNode(VGet(-200, 20, -100));*/

	m_onestavenue.get()->Init();
	m_meManager.get()->Init();
}

void SceneGame::Update()
{
	m_Idm.get()->Update();

#ifdef _DEBUG
	DebugDraw3D::Clear();
#endif // _DEBUG

	//ボタンを押した瞬間を判定する
	if (m_Idm->joyPad->isSTART == true && !isStartButtonPressed)
	{
		isStartButtonPressed = true;

		if (m_isOpenMenu == true)
		{
			m_isOpenMenu = false;
		}
		else
		{
			m_isOpenMenu = true;
		}

	}
	if (!m_Idm->joyPad->isSTART == true)
	{
		isStartButtonPressed = false;
	}



	//メニュー画面が開かれている場合とそうでない場合
	if (m_isOpenMenu == true)
	{
		m_gameMenu.get()->Update();
	}
	else
	{
		m_physics.get()->Update();
		m_hpBar.get()->Update();
		m_charaIcon.get()->Update();

		m_smallAricle.get()->Update(VAdd(m_player->GetPosition(), VGet(0, 10, 0)), VSub(m_player->GetPosition(), VGet(0, 10, 0)), 8.0f);
		m_ground.get()->Update(VAdd(m_player->GetPosition(), VGet(0, 10, 0)), VSub(m_player->GetPosition(), VGet(0, 10, 0)), 8.0f);
		
		m_meManager.get()->Update(VAdd(m_player->GetPosition(), VGet(0, 10, 0)), VSub(m_player->GetPosition(), VGet(0, 10, 0)), 8.0f);

		m_skyDome.get()->SetPosition(m_player->GetPosition());
		m_skyDome.get()->Update();
		m_player.get()->Update(m_physics, m_camera.get()->GetHAngle(), m_camera.get()->GetVAngle(), m_camera.get()->GetSinParam(), m_camera.get()->GetCosParam());
		
		m_enemy1.get()->HitTarget(m_player.get()->GetPosition(), 20.0f);
		m_path.get()->AddNode(m_player.get()->GetPosition());
		nextNode = m_player.get()->GetPosition();
		
		m_enemy1.get()->Update(m_physics);
		m_enemy2.get()->Update(m_physics);
		m_enemy3.get()->Update(m_physics);
		m_camera.get()->Update(m_player.get()->GetPosition(), m_enemy1.get()->GetPosition());
		m_light.get()->Update();

		
		//m_command.get()->Update();

		m_onestavenue.get()->Update();

		if (CheckHitKey(KEY_INPUT_G))
		{
			SceneManager::GetInstance().ChangeScene(SceneType::Result);
		}
	}
}

void SceneGame::Draw()
{
	DebugDraw();
	m_skyDome.get()->Draw();


	m_smallAricle.get()->Draw();
	m_ground.get()->Draw(m_player->GetPosition(), 100.0f);

	m_meManager.get()->Draw();

	m_enemy1.get()->Draw(m_physics);
	m_enemy2.get()->Draw(m_physics);
	m_enemy3.get()->Draw(m_physics);
	m_player.get()->Draw();
	m_light.get()->Draw();


#ifdef _DEBUG
	DebugDraw3D::Draw3D();
#endif // _DEBUG

	float hpRatio = static_cast<float>(hp) / maxhp;
	m_hpBar.get()->DrawArcHPBarWithThickness(1100, 600, 100, 70, DX_PI_F * 1.0f, DX_PI_F * 2.5f, hpRatio, 0x00ff00);
	m_charaIcon.get()->Draw();


	//メニュー画面が開かれていたら
	if (m_isOpenMenu == true)
	{
		m_gameMenu.get()->Draw();
	}
	
	if (m_player.get()->HitAttackCheck(m_enemy1.get()->GetPosition(), 20.0f) == true)
	{

		DrawFormatString(200, 20, 0xff00ff, "CheckAttack");

		
		DrawFormatString(200, 40, 0xff00ff, "HitAttack");
		if (hp > 0) hp--;
		else hp = 1000;
		
	}

	
	//m_command.get()->Draw();

	m_onestavenue.get()->Draw();
	
	//ドア移動処理
	if (m_onestavenue.get()->IsHitPosition(m_player->GetPosition(), 10.0f) == true)
	{
		DrawFormatString(600, 40, 0xffffff, "HitDoor");

		if (m_onestavenue.get()->IsHitPosition(m_player->GetPosition(), 0.1f) == true)
		{
			m_player.get()->SetPosition(VGet(0,0,0));
		}
	}

#ifdef _DEBUG
	DrawFormatString(600, 20, 0xffffff, "playerPos:x%f,y%f,z%f", m_player->GetPosition().x, m_player->GetPosition().y, m_player->GetPosition().z);
	DrawCapsule3D(VAdd(m_player->GetPosition(), VGet(0, 10, 0)), VSub(m_player->GetPosition(), VGet(0, 10, 0)), 8.0f, 5, 0xffffff, 0xffffff, false);
	DrawSphere3D(m_player.get()->GetPosition(), 100.0f, 5, 0xffffff, 0xffffff, false);
#endif // _DEBUG


}

void SceneGame::Final()
{
	m_skyDome.get()->Final();

	m_smallAricle.get()->Final();
	m_ground.get()->Final(); 

	m_meManager.get()->Final();

	m_player.get()->Final(m_physics);
	m_enemy1.get()->Final(m_physics);
	m_enemy2.get()->Final(m_physics);
	m_enemy3.get()->Final(m_physics);
	//m_command.get()->Final();

	m_gameMenu.get()->Final();
	m_light.get()->Final();

	m_hpBar.get()->Final();
	m_charaIcon.get()->Final();


	m_onestavenue.get()->Fianl();
}

void SceneGame::DebugDraw()
{
#ifdef _DEBUG
	DrawString(0, 20, "GameScene", 0xffffff, 16);
	
	debugWindow.UpdateDebugInfo(5, "gameScene");
#endif // _DEBUG
}
