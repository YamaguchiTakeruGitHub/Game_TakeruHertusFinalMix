#pragma once
#include "../SceneBase/SceneBase.h"

class SceneLoading : public SceneBase
{
public:
	SceneLoading();
	~SceneLoading() override;

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final();
};

