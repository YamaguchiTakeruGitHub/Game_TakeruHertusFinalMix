#pragma once
#include "../Base/Component.h"

/// <summary>
/// 位置・回転・スケールを管理
/// </summary>
class ComponentTransform : public Component
{
public:
	
	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

	
	VECTOR position;//位置
	VECTOR scale;	//スケール
	VECTOR rotation;//回転
	float angle;	//向き
};

