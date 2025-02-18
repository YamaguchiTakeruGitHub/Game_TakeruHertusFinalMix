#pragma once
#include "../SceneBase/SceneBase.h"

class SceneClear : public SceneBase
{
public:
	SceneClear();
	~SceneClear()override;

	void Init()override;
	void Update()override;
	void Draw()override;
	void Final()override;

private:

};

