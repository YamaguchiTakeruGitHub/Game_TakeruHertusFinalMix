#pragma once
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include <iostream>

class EffectLib
{
public:
	
	EffectLib(const char* _effectName);
	~EffectLib();

	
	void Init(const char* _effectName);

	void PlayEffectLib();

	
	void Update(VECTOR _newPos);

	void Draw();
	void Final();

private:

	struct Effect
	{
		int handle;
		int playHandle;
		VECTOR position;
		int time;
	}effect;

};

