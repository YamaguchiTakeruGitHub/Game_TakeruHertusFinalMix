#pragma once
#include "SceneBase.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	~SceneTitle();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

private:
	void DebugDraw();

	int m_nowSelect;
	bool m_isDUpButtonPressed;
	bool m_isDDownButtonPressed;
	bool m_isChangeSceneGame;
	int m_pushNow;
	int m_pushBefore;

	VECTOR m_NewGamePos;
	VECTOR m_LoadGamePos;
	VECTOR m_BackPos;
	VECTOR m_BackGroundPos;
	VECTOR m_ButtonPointPos;



	typedef enum
	{
		eMenu_NewGame,
		eMenu_LoadGame,
		eMenu_Back,
		eMenu_Num,
	}eMenu;

	

};

