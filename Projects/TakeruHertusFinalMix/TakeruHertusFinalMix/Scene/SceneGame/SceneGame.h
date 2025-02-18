#pragma once
#include "../SceneBase/SceneBase.h"
#include "SceneGameCommon.h"
#include "../../UI/UIManager.h"

#define PLAYER_MAX_HITCOLL			2048		// ��������R���W�����|���S���̍ő吔
#define PLAYER_ENUM_DEFAULT_SIZE		800.0f		// ���͂̃|���S�����o�Ɏg�p���鋅�̏����T�C�Y

// �X�e�[�W�֌W�̒�`
#define STAGECOLLOBJ_MAXNUM			256			// �ǉ��̃R���W�����I�u�W�F�N�g�̍ő吔

class SceneGame : public SceneBase
{
public:

	SceneGame();
	~SceneGame()override;

	void Init()override;
	void Update()override;
	void Draw()override;
	void Final()override;

private:


	/*�f�o�b�N*/
	void DebugInit();
	void DebugUpdate();
	void DebugDraw();
	void DebugFinal();

	/*�`���[�g���A��*/
	void TutorialResous();
	void TutorialInit();
	void TutorialUpdate();
	void TutorialDraw();
	void TutorialFinal();
	void Section2Collision();
	void Section3Collision();

	/*SevenWondersTown*/
	void SevenWondersTownInit();
	void SevenWondersTownUpdate();
	void SevenWondersTownDraw();
	void SevenWondersTownFinal();


	/*UI�}�l�[�W���[*/
	std::shared_ptr<UIManager> m_Ui;


	/*�����蔻��*/
	std::vector<VERTEX3D> vertexs;
	MV1_COLL_RESULT_POLY_DIM HitPolyDim[2];
	
	void PolygonInit();
	void PolygoUpdate(int _modelHandle);
	std::shared_ptr<Collision> m_collision;			//�����蔻��

	//�Z�N�V�����Q�ŏo�����锠
	struct box
	{
		VECTOR m_position;
		VECTOR m_size;
	}m_LeftBox, m_RightBox, m_FowerdBox;

	/*�G�̃X�|�[��*/
	std::shared_ptr<Enemy_Fox> m_enemyFox;
	void CheckSpawnTriggers();
	void DrawArcHPBarWithThickness(int centerX, int centerY, int outerRadius, int innerRadius, float startAngle, float endAngle, float hpRatio, unsigned int color);
		

	/*BGM�ESE*/
	int m_bgmHandle;
	int m_seHandle;
	void BGM_Update();
	void SE_Update();


	/*�I�u�W�F�N�g*/
	std::shared_ptr<Player> m_player;				//�v���C���[
	
	std::shared_ptr<Enemy_Doragon> m_enemyDoragon;	//�h���S���G
	

	std::shared_ptr<TSSword> m_tsSword;				//TS��
	std::shared_ptr<TSShield> m_tsShield;			//TS��
	std::shared_ptr<TSRod> m_tsRod;					//TS��

	std::shared_ptr<Camera> m_camera;				//�J����
	std::shared_ptr<MapTutorial> m_mapTutorial;		//�`���[�g���A���}�b�v
	std::shared_ptr<SkyDome> m_skyDome;				//�X�J�C�h�[��
	std::shared_ptr<Light> m_light;					//���C�g
	std::shared_ptr<ObjectEffecter> m_effect;		//�G�t�F�N�g

	std::shared_ptr<Command> m_command;				//�R�}���h

	std::shared_ptr<SavePoint> m_savePoint;			//�Z�[�u
	bool isSavePoint;
	int m_savePointCount;

	//�`���[�g���A���̃Z�N�V�����̔ԍ�
	int m_tutorialSectionNumber;

	/*�`���[�g���A���̉摜*/
	int m_Section1GraphHandle[2];//�Z�N�V�����P
	int m_Section2GraphHandle[7];//�Z�N�V�����Q
	int m_Section3GraphHandle[10];//�Z�N�V�����R
	int m_Section4GraphHandle[9];//�Z�N�V�����S
	int m_Section5GraphHandle[2];//�Z�N�V�����T

	/*�`���[�g���A���̃t���O*/
	bool m_isSectionSkip;

	/*�t�F�[�h�C���p*/
	float m_fadeAlpha;

	/*�Z�N�V�����\���p*/
	VECTOR m_nextSectionPosition;
	float m_nextSectionRadius;
	
	/*����̑I���̊i�[*/
	//1�F���A2�F���A3�F��
	int m_SelectWeponMyPower;

	//1�F���A2�F���A3�F��
	int m_SelectWeponGivPower;


	/*�Z�N�V�������o�p*/
	//�Z�N�V�����P
	float m_sectionTime;//�Z�N�V�����P�̎��Ԍo��
	float m_sectionMaxTime;//�ő厞��

	//�Z�N�V�����Q
	int m_section_2Time;//���݂̌o�ߎ���
	int m_section_2MaxTime;//�ő厞��
	bool m_isSection_2LeftBoxEvent;
	bool m_isSection_2RightBoxEvent;
	bool m_isSection_2FowerdBoxEvent;
	int m_section_2EventTime;
	int m_section_2EventMaxTime;
	bool m_isSection_2SelectFlag;

	//�Z�N�V�����R
	int m_section_3Time;
	int m_section_3MaxTime;
	bool m_isSection_3LeftBoxEvent;
	bool m_isSection_3RightBoxEvent;
	bool m_isSection_3FowerdBoxEvent;
	int m_section_3FinalAnserTime;
	bool m_isSection_3FinalAnser;
	float m_fadeAlpha_1;
	float m_fadeAlpha_2;
	bool m_isSection_3SelectFlag;
	VECTOR m_finalAnserSelecctBackGroundPos;
	VECTOR m_finalAnserSelectWeponPos;

	/*�Z�N�V�����S(start)*/
	int m_section_4EventTime;
	int m_section_4EventMaxTime;
	
	int m_fadeAlpha_Section4_1;

	int m_section_4EventTime_2;
	int m_section_4EventMaxTime_2;

	bool m_isSavePointEvent;
	int m_savePointEventPushBottonTime;

	float m_sectionChangeAlpher;

	float m_saveClearEventTime;
	/*�Z�N�V�����S(end)*/



	typedef enum
	{
		eSelectWepon_YES,
		eSelectWepon_NO,
		eSelectWepon_Num,

	}eSelectWepon;
	int nowSelectWepon;

	VECTOR selectWeponYesPos;
	VECTOR selectWeponNoPos;
	VECTOR selectWeponPointPos;
	VECTOR selectWeponNextPointPos;
	VECTOR selectWeponBackGroundPos;
	void QuestionSelectUpdate(int _nextSectionNumber);
	void QuestionSelectDraw();
	void QuestionSelectUpdate_2();
	void QuestionSelectDraw_2();


	/*�G�t�F�N�g�̃e�X�g*/
	int mt_effecthandle;
	int mt_playEffectHandle;
	int mt_effectTime;

	/*���[���h*/
	typedef enum
	{
		eWorld_Tutorial,		//�`���[�g���A���̃��[���h
		eWorld_SevenWondersTown,//���̃��[���h
		eWorld_Num,				//���[���h�̌�

	}eWorld;
	int nowWorld;//���݂̃��[���h

	int actionHandle;
};

