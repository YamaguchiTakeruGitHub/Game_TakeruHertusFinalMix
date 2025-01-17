#pragma once
#include <DxLib.h>
#include <memory>
#include "mapEventCommon.h"


class MapEventManager
{
public:
	MapEventManager();
	~MapEventManager();

	void Init();
	void Update(VECTOR _startpos, VECTOR _endpos, float _radius);
	void Draw();
	void Final();

private:
	std::shared_ptr<MapEventOne> m_meOne;



};

