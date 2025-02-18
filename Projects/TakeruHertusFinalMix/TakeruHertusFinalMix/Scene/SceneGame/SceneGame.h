#pragma once
#include "../SceneBase/SceneBase.h"
#include "SceneGameCommon.h"
#include "../../UI/UIManager.h"

#define PLAYER_MAX_HITCOLL			2048		// 処理するコリジョンポリゴンの最大数
#define PLAYER_ENUM_DEFAULT_SIZE		800.0f		// 周囲のポリゴン検出に使用する球の初期サイズ

// ステージ関係の定義
#define STAGECOLLOBJ_MAXNUM			256			// 追加のコリジョンオブジェクトの最大数

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


	/*デバック*/
	void DebugInit();
	void DebugUpdate();
	void DebugDraw();
	void DebugFinal();

	/*チュートリアル*/
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


	/*UIマネージャー*/
	std::shared_ptr<UIManager> m_Ui;


	/*当たり判定*/
	std::vector<VERTEX3D> vertexs;
	MV1_COLL_RESULT_POLY_DIM HitPolyDim[2];
	
	void PolygonInit();
	void PolygoUpdate(int _modelHandle);
	std::shared_ptr<Collision> m_collision;			//当たり判定

	//セクション２で出現する箱
	struct box
	{
		VECTOR m_position;
		VECTOR m_size;
	}m_LeftBox, m_RightBox, m_FowerdBox;

	/*敵のスポーン*/
	std::shared_ptr<Enemy_Fox> m_enemyFox;
	void CheckSpawnTriggers();
	void DrawArcHPBarWithThickness(int centerX, int centerY, int outerRadius, int innerRadius, float startAngle, float endAngle, float hpRatio, unsigned int color);
		

	/*BGM・SE*/
	int m_bgmHandle;
	int m_seHandle;
	void BGM_Update();
	void SE_Update();


	/*オブジェクト*/
	std::shared_ptr<Player> m_player;				//プレイヤー
	
	std::shared_ptr<Enemy_Doragon> m_enemyDoragon;	//ドラゴン敵
	

	std::shared_ptr<TSSword> m_tsSword;				//TS剣
	std::shared_ptr<TSShield> m_tsShield;			//TS盾
	std::shared_ptr<TSRod> m_tsRod;					//TS杖

	std::shared_ptr<Camera> m_camera;				//カメラ
	std::shared_ptr<MapTutorial> m_mapTutorial;		//チュートリアルマップ
	std::shared_ptr<SkyDome> m_skyDome;				//スカイドーム
	std::shared_ptr<Light> m_light;					//ライト
	std::shared_ptr<ObjectEffecter> m_effect;		//エフェクト

	std::shared_ptr<Command> m_command;				//コマンド

	std::shared_ptr<SavePoint> m_savePoint;			//セーブ
	bool isSavePoint;
	int m_savePointCount;

	//チュートリアルのセクションの番号
	int m_tutorialSectionNumber;

	/*チュートリアルの画像*/
	int m_Section1GraphHandle[2];//セクション１
	int m_Section2GraphHandle[7];//セクション２
	int m_Section3GraphHandle[10];//セクション３
	int m_Section4GraphHandle[9];//セクション４
	int m_Section5GraphHandle[2];//セクション５

	/*チュートリアルのフラグ*/
	bool m_isSectionSkip;

	/*フェードイン用*/
	float m_fadeAlpha;

	/*セクション表示用*/
	VECTOR m_nextSectionPosition;
	float m_nextSectionRadius;
	
	/*武器の選択の格納*/
	//1：剣、2：盾、3：杖
	int m_SelectWeponMyPower;

	//1：剣、2：盾、3：杖
	int m_SelectWeponGivPower;


	/*セクション演出用*/
	//セクション１
	float m_sectionTime;//セクション１の時間経過
	float m_sectionMaxTime;//最大時間

	//セクション２
	int m_section_2Time;//現在の経過時間
	int m_section_2MaxTime;//最大時間
	bool m_isSection_2LeftBoxEvent;
	bool m_isSection_2RightBoxEvent;
	bool m_isSection_2FowerdBoxEvent;
	int m_section_2EventTime;
	int m_section_2EventMaxTime;
	bool m_isSection_2SelectFlag;

	//セクション３
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

	/*セクション４(start)*/
	int m_section_4EventTime;
	int m_section_4EventMaxTime;
	
	int m_fadeAlpha_Section4_1;

	int m_section_4EventTime_2;
	int m_section_4EventMaxTime_2;

	bool m_isSavePointEvent;
	int m_savePointEventPushBottonTime;

	float m_sectionChangeAlpher;

	float m_saveClearEventTime;
	/*セクション４(end)*/



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


	/*エフェクトのテスト*/
	int mt_effecthandle;
	int mt_playEffectHandle;
	int mt_effectTime;

	/*ワールド*/
	typedef enum
	{
		eWorld_Tutorial,		//チュートリアルのワールド
		eWorld_SevenWondersTown,//町のワールド
		eWorld_Num,				//ワールドの個数

	}eWorld;
	int nowWorld;//現在のワールド

	int actionHandle;
};

