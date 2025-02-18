#pragma once
#include "../SceneBase/SceneBase.h"
#include "../../UI/UIManager.h"

class SceneDebug : public SceneBase
{
public:
	SceneDebug();
	~SceneDebug()override;

	void Init()override;
	void Update()override;
	void Draw()override;
	void Final()override;

private:
	void SelectPush();

	void SelectNow();


	std::shared_ptr<UIManager> m_UI;

	int m_nowSelect;
	bool m_isDUpButtonPressed;
	bool m_isDDownButtonPressed;
	bool m_isChangeSceneGame;
	int m_pushNow;
	int m_pushBefore;

	struct Position
	{
		VECTOR Title;
		VECTOR Game;
		VECTOR Result;
		VECTOR Clear;
		VECTOR Back;
		VECTOR nowPoint;
	}m_pos;

	typedef enum
	{
		eSelect_Title,
		eSelect_Game,
		eSelect_Result,
		eSelect_Clear,
		eSelect_Back,

		eSelect_Num,
	}eSelect;




	/*テストプログラム*/
	int time;
};

