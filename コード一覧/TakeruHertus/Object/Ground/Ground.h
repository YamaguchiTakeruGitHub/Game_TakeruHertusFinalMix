#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>


class Ground
{
public:
	Ground();
	~Ground();

	void Init();
	void Update(VECTOR _startpos, VECTOR _endpos, float _radius);
	void Draw(VECTOR _pos, float _radius);
	void Final();

	int GetmodelHandle() const { return  this->modelHandle; }

private:

	int trCount;
	int trColor;

	void DebugDraw();
	
	int modelHandle;
	VECTOR position;
	MV1_COLL_RESULT_POLY_DIM HitPolyDim;
	MV1_REF_POLYGONLIST mapPolygonList;
	std::vector<VERTEX3D> vertexs;
	VECTOR vertexPos;
	

	int i;
	VECTOR Pos1;
	VECTOR Pos2;

};

