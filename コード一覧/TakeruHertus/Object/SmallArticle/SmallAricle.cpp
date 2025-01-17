#include "SmallAricle.h"

SmallAricle::SmallAricle()
	: m_modelHandle()
	, m_position()
{
}

SmallAricle::~SmallAricle()
{
	MV1DeleteModel(m_modelHandle);
}

void SmallAricle::Init()
{
	m_modelHandle = MV1LoadModel("../Asset/3D/SmallArticle/Clock/clock_fbx.mv1");
	mapPolygonList = MV1GetReferenceMesh(m_modelHandle, -1, true);
	m_position = VGet(0, 0, 0);
}

void SmallAricle::Update(VECTOR _startpos, VECTOR _endpos, float _radius)
{
	HitPolyDim = MV1CollCheck_Capsule(m_modelHandle, -1, _startpos, _endpos, _radius);

	MV1SetPosition(m_modelHandle, m_position);
}

void SmallAricle::Draw()
{
	MV1DrawModel(m_modelHandle);


    if (HitPolyDim.HitNum >= 1)
    {
#ifdef _DEBUG
        DrawFormatString(700, 0, 0xffffff, "HitPolyNum : %d", HitPolyDim.HitNum);

        for (int i = 0; i < HitPolyDim.HitNum; i++)
        {
            DrawTriangle3D(HitPolyDim.Dim[i].Position[0],
                HitPolyDim.Dim[i].Position[1],
                HitPolyDim.Dim[i].Position[2], 0x00ffff, true);

            DrawFormatString(0, (i + 1) * 32, GetColor(255, 255, 255), "x=%f, y=%f ,z=%f", HitPolyDim.Dim[i].HitPosition.x, HitPolyDim.Dim[i].HitPosition.y, HitPolyDim.Dim[i].HitPosition.z);
        }




#endif // _DEBUG

    }

#ifdef _DEBUG

    for (int i = 0; i < mapPolygonList.PolygonNum; i++)
    {
        DrawLine3D(mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[0]].Position,
            mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[1]].Position,
            0xffff00);

        DrawLine3D(mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[1]].Position,
            mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[2]].Position,
            0xffff00);

        DrawLine3D(mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[2]].Position,
            mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[0]].Position,
            0xffff00);

    }

#endif // _DEBUG
}

void SmallAricle::Final()
{
	MV1DeleteModel(m_modelHandle);
    MV1CollResultPolyDimTerminate(HitPolyDim);
}
