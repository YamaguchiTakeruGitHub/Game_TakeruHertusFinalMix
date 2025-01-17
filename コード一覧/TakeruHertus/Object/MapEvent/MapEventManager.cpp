#include "MapEventManager.h"

MapEventManager::MapEventManager()
{
	m_meOne = std::make_shared<MapEventOne>();
}

MapEventManager::~MapEventManager()
{
}

void MapEventManager::Init()
{
	m_meOne->Init();
}

void MapEventManager::Update(VECTOR _startpos, VECTOR _endpos, float _radius)
{
	m_meOne->Update(_startpos, _endpos, _radius);
}

void MapEventManager::Draw()
{
	m_meOne->Draw();
}

void MapEventManager::Final()
{
	m_meOne->Final();
}
