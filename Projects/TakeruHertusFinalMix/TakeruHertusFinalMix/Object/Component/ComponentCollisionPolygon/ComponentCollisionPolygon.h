#pragma once
#include "../Base/Component.h"
#include "../ComponentModel/ComponentModel.h"

/// <summary>
/// �|���S���f�[�^(�����F_model)
/// </summary>
class ComponentCollisionPolygon : public Component
{
private:
	std::shared_ptr<ComponentModel> m_model;

public:
	ComponentCollisionPolygon(std::shared_ptr<ComponentModel> _model);

	void Init()		override;
	void Update()	override;
	void Draw()		override;
	void Final()	override;
	
	MV1_REF_POLYGONLIST polygonList;

	std::vector<VERTEX3D> vertexs;
	MV1_COLL_RESULT_POLY_DIM HitPolyDim;
};

