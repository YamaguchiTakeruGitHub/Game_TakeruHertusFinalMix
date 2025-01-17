#pragma once
#include <DxLib.h>
#include <vector>

class SmallAricle
{
public:
	SmallAricle();
	~SmallAricle();

	void Init();
	void Update(VECTOR _startpos, VECTOR _endpos, float _radius);
	void Draw();
	void Final();

private:
	int m_modelHandle;
	VECTOR m_position;

	MV1_COLL_RESULT_POLY_DIM HitPolyDim;
	MV1_REF_POLYGONLIST mapPolygonList;
	std::vector<VERTEX3D> vertexs;
};

