#pragma once
#include "../Entity/Entity.h"

class SkyDome : public Entity
{
public:
	SkyDome();

	void Init();
	void Update();
	void Draw(); 
	void Final();

	std::shared_ptr<ComponentModel> m_model;
	std::shared_ptr<ComponentTransform> m_transform;



	int time;
};

