#pragma once
#include "../Base/Component.h"

/// <summary>
/// �ʒu�E��]�E�X�P�[�����Ǘ�
/// </summary>
class ComponentTransform : public Component
{
public:
	
	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

	
	VECTOR position;//�ʒu
	VECTOR scale;	//�X�P�[��
	VECTOR rotation;//��]
	float angle;	//����
};

