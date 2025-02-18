#include "ComponentCollisionPolygon.h"

ComponentCollisionPolygon::ComponentCollisionPolygon(std::shared_ptr<ComponentModel> _model)
	: m_model(_model)
{
}

void ComponentCollisionPolygon::Init()
{
}

void ComponentCollisionPolygon::Update()
{
}

void ComponentCollisionPolygon::Draw()
{
#ifdef _DEBUG
	/*���f���̃��C���[�t���[����`��*/
	int i;
	for (i = 0; i < polygonList.PolygonNum; i++)
	{
		// �|���S�����`������O���_���g�p���ă��C���[�t���[����`�悷��
	// �F�͉��F
		DrawLine3D(
			polygonList.Vertexs[polygonList.Polygons[i].VIndex[0]].Position,
			polygonList.Vertexs[polygonList.Polygons[i].VIndex[1]].Position,
			0xffff00);

		DrawLine3D(
			polygonList.Vertexs[polygonList.Polygons[i].VIndex[1]].Position,
			polygonList.Vertexs[polygonList.Polygons[i].VIndex[2]].Position,
			0xffff00);

		DrawLine3D(
			polygonList.Vertexs[polygonList.Polygons[i].VIndex[2]].Position,
			polygonList.Vertexs[polygonList.Polygons[i].VIndex[0]].Position,
			0xffff00);
	}
#endif // _DEBUG
}

void ComponentCollisionPolygon::Final()
{
}
