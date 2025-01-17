#include "SceneManager.h"
#include "SceneCommon.h"

SceneManager::SceneManager()
{
	m_titleScene	= std::make_shared<SceneTitle>();
	m_gameScene		= std::make_shared<SceneGame>();
	m_resultScene	= std::make_shared<SceneResult>();
	m_clearScene	= std::make_shared<SceneClear>();

	m_currentScene = m_titleScene;
	/*m_currentScene.get()->Init();*/

}

SceneManager::~SceneManager()
{
	m_currentScene.get()->Final();
}

void SceneManager::ChangeScene(SceneType _newScene)
{
	m_currentScene.get()->Final();
	switch (_newScene)
	{
	case SceneType::Title:
		m_currentScene = m_titleScene;
		break;
	case SceneType::Game:
		m_currentScene = m_gameScene;
		break;
	case SceneType::Result:
		m_currentScene = m_resultScene;
		break;
	case SceneType::Clear:
		m_currentScene = m_clearScene;
		break;
	}
	m_currentScene.get()->Init();
}

void SceneManager::Init()
{
	m_currentScene->Init();
}

void SceneManager::Update()
{
	m_currentScene->Update();
}

void SceneManager::Draw()
{
	m_currentScene->Draw();
}

void SceneManager::Final()
{
	m_currentScene->Final();
}

void SceneManager::DebugDraw()
{
	m_currentScene->DebugDraw();
}
