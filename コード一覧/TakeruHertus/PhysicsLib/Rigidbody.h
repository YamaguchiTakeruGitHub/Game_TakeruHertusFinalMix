#pragma once
#include <DxLib.h>

/// <summary>
/// 当たり判定を適応するためのデータ
/// </summary>
class Rigidbody
{
public:
	Rigidbody();

	/// <summary>
	/// リジッドボディの初期化
	/// </summary>
	/// <param name="_useGravity">：重力を適応するか否か</param>
	void Init(bool _useGravity = false);

	const VECTOR& GetPosition() const { return m_position; }
	const VECTOR& GetDireciton() const { return m_direction; }
	const VECTOR& GetVelocity() const { return m_velocity; }
	bool UseGravity() const { return is_UseGravity; }

	void SetPosition(const VECTOR& _set) { m_position = _set; }
	void SetDirection(const VECTOR& _set) { m_direction = _set; }

	/// <summary>
	/// velocityのセットとdeirctionの自動計算
	/// </summary>
	/// <param name="_set"></param>
	void SetVelocity(const VECTOR& _set);

private:
	VECTOR m_position;
	VECTOR m_direction;
	VECTOR m_velocity;
	bool is_UseGravity;


};

