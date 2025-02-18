#pragma once
#include "../Base/Component.h"
#include "../ComponentTransform/ComponentTransform.h"

/// <summary>
/// ���f���`��R���|�[�l���g
/// </summary>
class ComponentModel : public Component
{
public:
	~ComponentModel() override;

	/// <summary>
	/// ���f���̃��[�h������
	/// </summary>
	/// <param name="_filePath">3DmodelPath</param>
	void LoadModel(const char* _filePath);

	/// <summary>
	/// ���f�����擾����
	/// </summary>
	/// <returns>modelHandle</returns>
	int GetModel() const { return modelHandle; }

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;
	

	int modelHandle;//���f���̃n���h��
};

