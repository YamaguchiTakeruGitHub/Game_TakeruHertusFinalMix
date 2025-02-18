#pragma once
#include "../Component/Base/Component.h"
#include "../../Object/Component/Base/ComponentCommon.h"

/// <summary>
/// すべてのオブジェクトを仲介するクラス（別名Acter）
/// </summary>
class Entity
{
private:
	std::unordered_map<std::string, std::shared_ptr<Component>> components;

protected:/*以下は継承先のインスタンス生成時にアクセスできないようにプロテクト*/

	/// <summary>
	/// コンポーネントを生成する
	/// </summary>
	template<typename T, typename... Args>
	void AddComponent(Args&&... args)
	{
		components[typeid(T).name()] = std::make_shared<T>(std::forward<Args>(args)...);
	}

	/// <summary>
	/// コンポーネントを取得する
	/// </summary>
	template<typename T>
	std::shared_ptr<T> GetComponent()
	{
		auto it = components.find(typeid(T).name());
		if (it != components.end())
		{
			return std::dynamic_pointer_cast<T>(it->second);
		}
		return nullptr;
	}

	/// <summary>
	/// <para>《 ユーザー定義：コンポーネントの初期化 》</para>
	/// <para>オブジェクトの初期化前後に追加する</para>
	/// </summary>
	void InitComponents();

	/// <summary>
	/// <para>《 ユーザー定義：コンポーネントの更新 》</para>
	/// <para>オブジェクトの更新前後に追加する</para>
	/// </summary>
	void UpdateComponents();

	/// <summary>
	/// <para>《 ユーザー定義：コンポーネントの描画 》</para>
	/// <para>オブジェクトの描画前後に追加する</para>
	/// </summary>
	void DrawComponents();

	/// <summary>
	/// <para>《 ユーザー定義：コンポーネントの解放 》</para>
	/// <para>オブジェクトの解放前後に追加する</para>
	/// </summary>
	void FinalComponents();
	
};

