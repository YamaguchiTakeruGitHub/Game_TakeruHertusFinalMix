#pragma once
#include "../Base/Component.h"
#include "../ComponentTransform/ComponentTransform.h"

class ComponentCollisionCapsule : public Component
{
private:
	std::shared_ptr<ComponentTransform> m_transform;

public:
	ComponentCollisionCapsule(std::shared_ptr<ComponentTransform> _transform);

	void Init()		override;
	void Update()	override;
	void Draw()		override;
	void Final()	override;

	VECTOR maxPosition;//頭のポジション
	VECTOR minPosition;//足元のポジション
	float radius;//カプセルの半径
	float size;//ポジションからカプセルの上下のサイズ
};

