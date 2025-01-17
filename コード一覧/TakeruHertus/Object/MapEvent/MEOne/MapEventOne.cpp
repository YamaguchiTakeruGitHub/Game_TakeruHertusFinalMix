
#include "MapEventOne.h"

MapEventOne::MapEventOne()
	: modelHandle(-1)
	, position(VGet(0, 0, 0))
	, angle(0.0f)
{
}

MapEventOne::~MapEventOne()
{
	MV1DeleteModel(modelHandle);
}

void MapEventOne::Init()
{
	modelHandle = MV1LoadModel("../Asset/3D/mapEvent/mapEventOne.mv1");
	position = VGet(300, 50, 300);
	angle = 0.0f;
}

void MapEventOne::Update(VECTOR _startpos, VECTOR _endpos, float _radius)
{
	if (angle >= 360.0f)
	{
		angle = 0.0f;
	}
	else
	{
		angle += 0.01f;
	}

	MV1SetPosition(modelHandle, position);
	MV1SetRotationXYZ(modelHandle, VGet(0, 0, angle));

}

void MapEventOne::Draw()
{
	MV1DrawModel(modelHandle);
}

void MapEventOne::Final()
{
	
	MV1DeleteModel(modelHandle);
}
