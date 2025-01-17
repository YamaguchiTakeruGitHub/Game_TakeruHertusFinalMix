#pragma once
#include "SceneBase.h"

class SceneClear : public SceneBase
{
public:
	SceneClear();
	~SceneClear();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

private:
	void DebugDraw();


};

