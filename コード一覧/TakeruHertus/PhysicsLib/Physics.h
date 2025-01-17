#pragma once
#include <list>
#include <vector>
#include <cassert>

#include "PhysicsLib.h"
#include "../MathLib/MathLib.h"

class Collidable;

class Physics final
{
public:

	/// <summary>
	/// 衝突物の登録
	/// </summary>
	/// <param name="_collidable"></param>
	void Entry(std::shared_ptr<Collidable> _collidable);

	/// <summary>
	/// 衝突物の登録解除
	/// </summary>
	/// <param name="_collidable"></param>
	void Exit(std::shared_ptr<Collidable> _collidable);

	/// <summary>
	/// 更新（登録オブジェクトの物理移動、衝突通知）
	/// </summary>
	void Update();

	std::list<std::shared_ptr<Collidable>> IsCollideLine(const VECTOR& _start, const VECTOR& _end) const;

	static constexpr float m_gravity = -0.01f;
	static constexpr float m_maxGravityAccel = -0.15f;

private:
	static const int BeforFixInfoColor = 0x0000ff;//補正前情報色
	static const int AimInfoColor	   = 0x0000aa;//補正前予定情報色
	static const int AfterFixInfoColor = 0xff00ff;//補正後情報色

	//登録されたCollidableのリスト
	std::list<std::shared_ptr<Collidable>> m_collidables;

	//遅延通知のためのデータ
	struct OnCollideInfo
	{
		std::shared_ptr<Collidable> owner = std::make_shared<Collidable>();
		std::shared_ptr<Collidable> colider = std::make_shared<Collidable>();
		void OnCollide();
	};


	//当たり判定のチェック
	std::vector<OnCollideInfo> CheckColide() const;

	//衝突しているか否か
	bool IsCollide(const std::shared_ptr<Collidable> _objA, const std::shared_ptr<Collidable> _objB) const;

	//位置の補正
	void FixNextPosition(std::shared_ptr<Collidable> _primary, std::shared_ptr<Collidable> _secondary) const;

	//位置の確定
	void FixPosition();
	
};

