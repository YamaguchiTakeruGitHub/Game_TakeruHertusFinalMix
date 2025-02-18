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

	VECTOR maxPosition;//���̃|�W�V����
	VECTOR minPosition;//�����̃|�W�V����
	float radius;//�J�v�Z���̔��a
	float size;//�|�W�V��������J�v�Z���̏㉺�̃T�C�Y
};

