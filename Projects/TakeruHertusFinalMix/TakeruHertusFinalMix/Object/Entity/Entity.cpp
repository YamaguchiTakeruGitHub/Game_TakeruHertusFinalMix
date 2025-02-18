#include "Entity.h"



void Entity::InitComponents()
{
	for (auto& pair : components)
	{
		auto& component = pair.second;
		component->Init();
	}
}

void Entity::UpdateComponents()
{
	for (auto& pair : components)
	{
		auto& component = pair.second;
		component->Update();
	}
}

void Entity::DrawComponents()
{
	for (auto& pair : components)
	{
		auto& component = pair.second;
		component->Draw();
	}
}

void Entity::FinalComponents()
{
	for (auto& pair : components)
	{
		auto& components = pair.second;
		components->Final();
	}
}


