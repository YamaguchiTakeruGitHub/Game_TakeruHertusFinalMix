#pragma once
#include "../Base/Component.h"



class ComponentRightBody : public Component
{
public:

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

	void NormalizeDirection();

	VECTOR velocity;
	VECTOR direction;
	float speed;
};

//MEMO�i2025.1.15home�j�F�����f�[�^�̐݌v���J�n����
