#pragma once
#include "../Base/Component.h"

class ComponentPolygonDraw : public Component
{
private:

public:
	
	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;


	MV1_REF_POLYGONLIST m_mapPolygonList;
	std::vector<VERTEX3D> m_vertexs;

};

