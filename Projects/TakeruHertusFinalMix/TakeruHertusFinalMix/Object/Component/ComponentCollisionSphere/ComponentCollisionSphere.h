#pragma once
#include "../Base/Component.h"
#include "../ComponentTransform/ComponentTransform.h"

/// <summary>
/// 球体データ(引数：_transform)
/// </summary>
class ComponentCollisionSphere : public Component
{
private:
	std::shared_ptr<ComponentTransform> m_transform;

public:
	ComponentCollisionSphere(std::shared_ptr<ComponentTransform> _transform);

	void Init()		override;
	void Update()	override;
	void Draw()		override;
	void Final()	override;

	float radius;

};

