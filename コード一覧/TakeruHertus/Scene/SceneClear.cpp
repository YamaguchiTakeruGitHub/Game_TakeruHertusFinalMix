#include "SceneClear.h"
#include "SceneManager.h"

SceneClear::SceneClear()
{
}

SceneClear::~SceneClear()
{
}

void SceneClear::Init()
{
	m_Idm.get()->Init();
}

void SceneClear::Update()
{
	m_Idm.get()->Update();

	if (CheckHitKey(KEY_INPUT_C))
	{
		SceneManager::GetInstance().ChangeScene(SceneType::Title);
	}
}

void SceneClear::Draw()
{
	DebugDraw();
}

void SceneClear::Final()
{
}

void SceneClear::DebugDraw()
{
#ifdef _DEBUG
	DrawString(0, 20, "ClearScene", 0xffffff, 16);
#endif // _DEBUG

}
