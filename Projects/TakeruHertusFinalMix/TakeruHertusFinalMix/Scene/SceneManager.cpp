#include "SceneManager.h"
#include "SceneCommon.h"


//���݂͊e�V�[���Ŕ񓯊��ǂݍ��݂̃��[�h�������s���Ă��邪����̓}�l�[�W���[�ōs����悤�ɂ�����

SceneManager::SceneManager()
{
	m_titleScene = std::make_shared<SceneTitle>();
	m_gameScene = std::make_shared<SceneGame>();
	m_resultScene = std::make_shared<SceneResult>();
	m_clearScene = std::make_shared<SceneClear>();
	m_loadingScene = std::make_shared<SceneLoading>();

	//�f�o�b�N�p�V�[���ϐ�
	m_debugScene = std::make_shared<SceneDebug>();

#ifdef _DEBUG
	//�f�o�b�N��
	m_curreentScene = m_debugScene;
#else
	//�����[�X��
	m_curreentScene = m_titleScene;
#endif // _DEBUG

}

SceneManager::~SceneManager()
{
	m_curreentScene.get()->Final();
}

void SceneManager::ChangeScene(SceneType _newScene)
{
	m_curreentScene.get()->Final();
	switch (_newScene)
	{
	case SceneType::Title:
		m_curreentScene = m_titleScene;
		break;
	case SceneType::Game:
		m_curreentScene = m_gameScene;
		break;
	case SceneType::Result:
		m_curreentScene = m_resultScene;
		break;
	case SceneType::Clear:
		m_curreentScene = m_clearScene;
		break;
	case SceneType::Loading:
		m_curreentScene = m_loadingScene;
		break;

#ifdef _DEBUG
	case SceneType::Debug:
		m_curreentScene = m_clearScene;
		break;
#endif // _DEBUG


	}

	m_curreentScene.get()->Init();

}

void SceneManager::Init()
{
	m_curreentScene->Init();
}

void SceneManager::Update()
{
	m_curreentScene->Update();
}

void SceneManager::Draw()
{
	m_curreentScene->Draw();
}

void SceneManager::Final()
{
	m_curreentScene->Final();
}

