#pragma once
#include "../Base/Component.h"
#include "../ComponentTransform/ComponentTransform.h"

/// <summary>
/// モデル描画コンポーネント
/// </summary>
class ComponentModel : public Component
{
public:
	~ComponentModel() override;

	/// <summary>
	/// モデルのロードをする
	/// </summary>
	/// <param name="_filePath">3DmodelPath</param>
	void LoadModel(const char* _filePath);

	/// <summary>
	/// モデルを取得する
	/// </summary>
	/// <returns>modelHandle</returns>
	int GetModel() const { return modelHandle; }

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;
	

	int modelHandle;//モデルのハンドル
};

