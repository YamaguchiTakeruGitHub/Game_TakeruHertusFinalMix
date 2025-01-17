#pragma once
#include "SceneBase.h"

class SceneBase;
class SceneManager
{
public:
	SceneManager();
	~SceneManager();


	void Init();
	void Update();
	void Draw();
	void Final();

	void DebugDraw();

	static SceneManager& GetInstance() { static SceneManager instance; return instance; }

	void ChangeScene(SceneType _newScene);

private:
	std::shared_ptr<SceneBase> m_currentScene;
	std::shared_ptr<SceneBase> m_titleScene;
	std::shared_ptr<SceneBase> m_gameScene;
	std::shared_ptr<SceneBase> m_resultScene;
	std::shared_ptr<SceneBase> m_clearScene;

};

