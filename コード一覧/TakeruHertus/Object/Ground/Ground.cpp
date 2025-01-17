#include "Ground.h"

// ƒ‰ƒCƒ“‚ð•`‚­”ÍˆÍ
#define LINE_AREA_SIZE				10000.0f

// ƒ‰ƒCƒ“‚Ì”
#define LINE_NUM					50

Ground::Ground()
    : modelHandle(-1)
    , position(VGet(0,0,0))
    , vertexPos(VGet(0,0,0))
    , trColor(0)
    , trCount(0)

{
}

Ground::~Ground()
{
    MV1DeleteModel(modelHandle);
}

void Ground::Init()
{
   // modelHandle = MV1LoadModel("../Asset/3D/map/mapkari.mv1");
  modelHandle = MV1LoadModel("../Asset/3D/map/ground.mv1");

    mapPolygonList = MV1GetReferenceMesh(modelHandle, -1, true);

    position = VGet(0, 0, 0);
    vertexPos = VGet(0, 0, 0);
   
    trColor = 0;
    trCount = 0;

}

void Ground::Update(VECTOR _startpos, VECTOR _endpos, float _radius)
{
    HitPolyDim = MV1CollCheck_Capsule(modelHandle, -1, _startpos, _endpos, _radius);

    

    MV1SetPosition(modelHandle, position);
}

void Ground::Draw(VECTOR _pos, float _radius)
{
    MV1DrawModel(modelHandle);
    DebugDraw();

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

            vertexPos = HitPolyDim.Dim[i].HitPosition;




            if (trCount >= 255 * 3)
            {
                trCount = 0;
            }
            else
            {
                
                trCount++;

                if (trCount >= 0 && trCount <= 255)
                {
                    trColor = GetColor(trCount, 0, 0);
                }
                if (trCount >= 255 && trCount <= 510)
                {

                    trColor = GetColor(0, trCount, 0);
                }
                if (trCount >= 510 && trCount <= trCount * 3)
                {

                    trColor = GetColor(0, 0, trCount);
                }
            }




        }

#endif // _DEBUG
    }

#ifdef _DEBUG

   

    for (int i = 0; i < mapPolygonList.PolygonNum; i++)
    {
       
        bool maxpp = _pos.x + _radius >= mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[0]].Position.x &&
            _pos.y + _radius >= mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[0]].Position.y &&
            _pos.z + _radius >= mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[0]].Position.z &&
            _pos.x + _radius >= mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[1]].Position.x &&
            _pos.y + _radius >= mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[1]].Position.y &&
            _pos.z + _radius >= mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[1]].Position.z &&
            _pos.x + _radius >= mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[2]].Position.x &&
            _pos.y + _radius >= mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[2]].Position.y &&
            _pos.z + _radius >= mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[2]].Position.z;


        bool minpp = _pos.x - _radius <= mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[0]].Position.x &&
            _pos.y - _radius <= mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[0]].Position.y &&
            _pos.z - _radius <= mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[0]].Position.z &&
            _pos.x - _radius <= mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[1]].Position.x &&
            _pos.y - _radius <= mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[1]].Position.y &&
            _pos.z - _radius <= mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[1]].Position.z &&
            _pos.x - _radius <= mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[2]].Position.x &&
            _pos.y - _radius <= mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[2]].Position.y &&
            _pos.z - _radius <= mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[2]].Position.z;
      
        if (maxpp && minpp)
        {
        DrawLine3D(mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[0]].Position,
                   mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[1]].Position,
                   trColor);
          //  0xffff00);

        DrawLine3D(mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[1]].Position,
                   mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[2]].Position,
                   trColor);
            //0xffff00);

        DrawLine3D(mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[2]].Position,
                   mapPolygonList.Vertexs[mapPolygonList.Polygons[i].VIndex[0]].Position,
                   trColor);
            //0xffff00);

        }
            

    }

#endif // _DEBUG
 
}

void Ground::Final()
{
    MV1CollResultPolyDimTerminate(HitPolyDim);

    MV1DeleteModel(modelHandle);
}






void Ground::DebugDraw()
{
  

    SetUseZBufferFlag(TRUE);

    Pos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
    Pos2 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, LINE_AREA_SIZE / 2.0f);
    for (i = 0; i <= LINE_NUM; i++)
    {
        DrawLine3D(Pos1, Pos2, GetColor(255, 255, 255));
        Pos1.x += LINE_AREA_SIZE / LINE_NUM;
        Pos2.x += LINE_AREA_SIZE / LINE_NUM;
    }

    Pos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
    Pos2 = VGet(LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
    for (i = 0; i < LINE_NUM; i++)
    {
        DrawLine3D(Pos1, Pos2, GetColor(255, 255, 255));
        Pos1.z += LINE_AREA_SIZE / LINE_NUM;
        Pos2.z += LINE_AREA_SIZE / LINE_NUM;
    }

    SetUseZBufferFlag(FALSE);
}

