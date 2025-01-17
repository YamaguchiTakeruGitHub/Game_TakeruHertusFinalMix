#pragma once
#include "SceneBase.h"
#include "SceneGameCommon.h"
#include "../Object/Ground/Ground.h"
#include <memory>
#include "../DebugWindow/DebugWindow.h"
#include "../System/GemeMenu/GameMenu.h"
#include "../System/HPBar/HPBar.h"
#include "../Object/SmallArticle/SmallAricle.h"

#include "../Object/Door/OneStAvenue/OneStAvenue.h"

#include "../Object/MapEvent/MapEventManager.h"

class SceneGame : public SceneBase
{
public:
	SceneGame();
	~SceneGame();

	void Init();
	void Update();
	void Draw();
	void Final();
	void DebugDraw();

private:
	bool m_isOpenMenu;

	bool isStartButtonPressed;

	float hp;
	float maxhp;


private:
	DebugWindow debugWindow;

	std::shared_ptr<Path> m_path;
	std::shared_ptr<CharacterIcon> m_charaIcon;
	std::shared_ptr<HPBar> m_hpBar;
	std::shared_ptr<Player> m_player;
	std::shared_ptr<EnemySmallFish> m_enemy1;
	std::shared_ptr<EnemyMidle> m_enemy2;
	std::shared_ptr<EnemyDinamic> m_enemy3;
	std::shared_ptr<Camera> m_camera;
	std::shared_ptr<Ground> m_ground;
	std::shared_ptr<SmallAricle> m_smallAricle;
	std::shared_ptr<Physics> m_physics;
	std::shared_ptr<SkyDome> m_skyDome;
	std::shared_ptr<LightManager> m_light;
	std::shared_ptr<GameMenu> m_gameMenu;
	//std::shared_ptr<Command> m_command;
	
	std::shared_ptr<OneStAvenue> m_onestavenue;
	std::shared_ptr<MapEventManager> m_meManager;

	VECTOR nextNode;


private:
	

};

