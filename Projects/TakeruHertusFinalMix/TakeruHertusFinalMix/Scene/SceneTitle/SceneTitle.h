#pragma once
#include "../SceneBase/SceneBase.h"
#include "../../UI/UIManager.h"
#include <random>
#include "../../UI/Easing/Easing.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	~SceneTitle()override;

	void InitResource();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

private:
	
	Easing m_easing;

	std::shared_ptr<UIManager> m_UI;
	std::shared_ptr<InputDeviceManager> m_Idm;
	
	VECTOR m_newGamePosition;
	VECTOR m_loadGamePosition;
	VECTOR m_backPosition;

	VECTOR m_buttonPointPosition;
	VECTOR m_titleBackGroundPosition;
	VECTOR m_titleSelectPosition;
	VECTOR m_titleRogoPosition;

	VECTOR m_titleOPPPosition;

	int m_titleBackGroundGraphHandle;
	int m_buttonPointGraphHandle;
	int m_titleSelectGraphHandle;
	int m_titleRogoGraphHandle;
	int m_titleOPPGraphHandle;

	int m_titleSelectNewGameGraphHandle;
	int m_titleSelectLoadGraphHandle;
	int m_titleSelectBackGraphHandle;

	int m_nowSelect;
	int m_prevSelect;
	int m_pushBefore;
	int m_pushNow;

	bool m_isDDownButtonPressed;
	bool m_isDUpButtonPressed;

	/*選択肢の種類*/
	typedef enum
	{
		eSelect_NewGame,
		eSelect_LoadGame,
		eSelect_Back,
		eSelect_Num,
	}eSelect;



	/*セレクト関連*/
	void SelectPush();
	void SelectNow();
	void SelectEfect();

	/*時間*/
	float time;

	/*回転エフェクト*/
	VECTOR circlePos;
	
	/*フェードイン用*/
	float m_fadeAlpha;

	/*BGM・SE*/
	int m_bgmHandle;
	int m_seHandle;
	void BGM_Update();
	int m_pushCutTime;//非同期読み込みからたいとるに遷移する際に時間をとって判定させないようにする。

	/*非同期読み込み*/
	bool isLoading;
	int resourceNum;

	/*タイトル画面データ*/
	bool isTitlePlayeing;
	void TitleUpdate();
	void TitleDraw();
	
	/*LoadGameデータ*/
	bool isLoadGame;
	void LoadGameUpdate();
	void LoadGameDraw();
	int loadGameBackGroundGraphHandle;
	VECTOR loadGameBackGroundGraphPosition;

	int loadGameMenuGraphHandle[4];
	VECTOR loadGameMenuPos[4];

	//セレクトの背景
	int loadGameMenuSelectBackGroundGraphHandle;
	VECTOR loadGameMenuSelectBackGroundPosition;

	//セレクト番号
	int loadGameMenuSelectNumberGraphHandle[4];
	VECTOR loadGameMenuSelectNumberPosition[4];

	//セレクト非選択状態
	int loadGameMenuSelectGraphHandle[4];
	VECTOR loadGameMenuSelectPosition[4];

	//セレクト選択状態
	int loadGameMenuSelectOnGraphHandle[4];
	VECTOR loadGameMenuSelectOnPosition[4];

	typedef enum
	{
		eLGM_Select_1,
		eLGM_Select_2,
		eLGM_Select_3,
		eLGM_Select_4,
		eLGM_Select_Num,
	}eLGM_Select;
	int m_loadGameMenuSelectNowSelect;

	/*パーティクル*/
	int m_selectParticle;

	float easingTime;

	/*NewGameデータ*/
	bool isNewGame;

};

