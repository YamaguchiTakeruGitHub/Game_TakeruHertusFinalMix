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

	/*�I�����̎��*/
	typedef enum
	{
		eSelect_NewGame,
		eSelect_LoadGame,
		eSelect_Back,
		eSelect_Num,
	}eSelect;



	/*�Z���N�g�֘A*/
	void SelectPush();
	void SelectNow();
	void SelectEfect();

	/*����*/
	float time;

	/*��]�G�t�F�N�g*/
	VECTOR circlePos;
	
	/*�t�F�[�h�C���p*/
	float m_fadeAlpha;

	/*BGM�ESE*/
	int m_bgmHandle;
	int m_seHandle;
	void BGM_Update();
	int m_pushCutTime;//�񓯊��ǂݍ��݂��炽���Ƃ�ɑJ�ڂ���ۂɎ��Ԃ��Ƃ��Ĕ��肳���Ȃ��悤�ɂ���B

	/*�񓯊��ǂݍ���*/
	bool isLoading;
	int resourceNum;

	/*�^�C�g����ʃf�[�^*/
	bool isTitlePlayeing;
	void TitleUpdate();
	void TitleDraw();
	
	/*LoadGame�f�[�^*/
	bool isLoadGame;
	void LoadGameUpdate();
	void LoadGameDraw();
	int loadGameBackGroundGraphHandle;
	VECTOR loadGameBackGroundGraphPosition;

	int loadGameMenuGraphHandle[4];
	VECTOR loadGameMenuPos[4];

	//�Z���N�g�̔w�i
	int loadGameMenuSelectBackGroundGraphHandle;
	VECTOR loadGameMenuSelectBackGroundPosition;

	//�Z���N�g�ԍ�
	int loadGameMenuSelectNumberGraphHandle[4];
	VECTOR loadGameMenuSelectNumberPosition[4];

	//�Z���N�g��I�����
	int loadGameMenuSelectGraphHandle[4];
	VECTOR loadGameMenuSelectPosition[4];

	//�Z���N�g�I�����
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

	/*�p�[�e�B�N��*/
	int m_selectParticle;

	float easingTime;

	/*NewGame�f�[�^*/
	bool isNewGame;

};

