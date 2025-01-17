#pragma once
#include <DxLib.h>
class LightManager
{
public:
	LightManager();
	~LightManager();

	void Init();
	void Update();
	void Draw();
	void Final();

private:
	struct DirectionLight
	{
		int handle;
		VECTOR postion;


	}m_DirLight;

};

