#pragma once
#include <DxLib.h>

class OneStAvenue
{
public:
	OneStAvenue();
	~OneStAvenue();

	void Init();
	void Update();
	void Draw();
	void Fianl();

	bool IsHitPosition(VECTOR _pos, float _radius);

private:
	VECTOR position;
	float radius;


};

