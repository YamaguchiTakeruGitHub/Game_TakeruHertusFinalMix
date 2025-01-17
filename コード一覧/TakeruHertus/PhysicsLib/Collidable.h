#pragma once
#include "GameObjectTag.h"//ゲームオブジェクトのタグ
#include "PhysicsLib.h"//物理ライブラリ


class Rigidbody;
class Physics;
class ColliderData;

/// <summary>
/// 衝突ができるもの、物理や衝突判定を行う場合はこれを継承させる
/// </summary>
class Collidable abstract//明示的に抽象クラスにする
{
public:

	//位置補正の優先順位の判別
	enum class Priority : int
	{
		Low,		//低
		High,		//高
		Static,		//動かない
	};

	Collidable(Priority _prioriy, GameObjectTag _tag, ColliderData::Kind _colliderKind);
	virtual ~Collidable();
	virtual void Init(std::shared_ptr<Physics> _physics);
	virtual void Final(std::shared_ptr<Physics> _physics);

	///// <summary>
	///// 衝突した時
	///// </summary>
	///// <param name="_collider"></param>
	//virtual void OnCollide(const Collidable& _collider) abstract;//明示的に抽象化する

	/// <summary>
	/// 衝突した時
	/// </summary>
	/// <param name="_collider"></param>
	virtual void OnCollide(const std::shared_ptr<Collidable>& _collider) abstract;//明示的に抽象化する



	/// <summary>
	/// タグ情報
	/// </summary>
	/// <returns></returns>
	GameObjectTag GetTag() const { return m_tag; }

	/// <summary>
	/// 優先度
	/// </summary>
	/// <returns></returns>
	Priority GetPriority() const { return m_priority; }


protected:
	Rigidbody m_righdbody;						//物理データ
	std::shared_ptr<ColliderData> m_colliderData;	//当たり判定データ

private:

	/// <summary>
	/// 当たり判定の種類を生成する
	/// </summary>
	/// <param name="_kind"></param>
	/// <returns></returns>
	std::shared_ptr<ColliderData> CreateColliderData(ColliderData::Kind _kind);

	GameObjectTag m_tag;
	
	Priority m_priority;

	//PhysicsクラスがCollidableを自由に管理するためにフレンド化（どんな区域でもアクセスできる）
	friend Physics;

private:
	VECTOR m_nextPos;

};

