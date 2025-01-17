#pragma once
#include "SceneBase.h"

class SceneResult : public SceneBase
{
public:
	SceneResult();
	~SceneResult();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

private:
	void DebugDraw();


};

