#pragma once
#include <DxLib.h>

class CharacterIcon
{
public:
	CharacterIcon();
	~CharacterIcon();

	void Init();
	void Update();
	void Draw();
	void Final();

private:
	VECTOR position;
	int imgHandle;
};

