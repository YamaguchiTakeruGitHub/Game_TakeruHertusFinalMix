#include "SceneResult.h"
#include "SceneManager.h"

SceneResult::SceneResult()
{
}

SceneResult::~SceneResult()
{
}

void SceneResult::Init()
{
	m_Idm.get()->Init();
}

void SceneResult::Update()
{
	m_Idm.get()->Init();


	if (CheckHitKey(KEY_INPUT_R))
	{
		SceneManager::GetInstance().ChangeScene(SceneType::Clear);
	}
}

void SceneResult::Draw()
{
	DebugDraw();
}

void SceneResult::Final()
{
}

void SceneResult::DebugDraw()
{
#ifdef _DEBUG
	DrawString(0, 20, "ResultScene", 0xffffff, 16);

#endif // _DEBUG

}
