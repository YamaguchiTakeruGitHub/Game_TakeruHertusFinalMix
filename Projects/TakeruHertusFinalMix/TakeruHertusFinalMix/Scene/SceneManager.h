#pragma once
#include "SceneBase/SceneBase.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void Update();
	void Draw();
	void Final();

	static SceneManager& GetInstance() { static SceneManager instance; return instance; }

	void ChangeScene(SceneType _newScene);

private:
	std::shared_ptr<SceneBase> m_curreentScene;
	std::shared_ptr<SceneBase> m_titleScene;
	std::shared_ptr<SceneBase> m_gameScene;
	std::shared_ptr<SceneBase> m_resultScene;
	std::shared_ptr<SceneBase> m_clearScene;
	std::shared_ptr<SceneBase> m_loadingScene;
	//デバック用シーン変数
	std::shared_ptr<SceneBase> m_debugScene;
};

