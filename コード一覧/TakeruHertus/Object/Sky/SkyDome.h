#pragma once
#include <DxLib.h>

class SkyDome
{
public:
	SkyDome();
	~SkyDome();

	void Init();
	void Update();
	void Draw();
	void Final();

	void SetPosition(const VECTOR& _position) { this->position = _position; }
	VECTOR GetPosition() const { return  this->position; }

private:

	int modelHandle;
	VECTOR position;
	float m_angle;
};

