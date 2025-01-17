#pragma once
#include <DxLib.h>

/// <summary>
/// �����蔻���K�����邽�߂̃f�[�^
/// </summary>
class Rigidbody
{
public:
	Rigidbody();

	/// <summary>
	/// ���W�b�h�{�f�B�̏�����
	/// </summary>
	/// <param name="_useGravity">�F�d�͂�K�����邩�ۂ�</param>
	void Init(bool _useGravity = false);

	const VECTOR& GetPosition() const { return m_position; }
	const VECTOR& GetDireciton() const { return m_direction; }
	const VECTOR& GetVelocity() const { return m_velocity; }
	bool UseGravity() const { return is_UseGravity; }

	void SetPosition(const VECTOR& _set) { m_position = _set; }
	void SetDirection(const VECTOR& _set) { m_direction = _set; }

	/// <summary>
	/// velocity�̃Z�b�g��deirction�̎����v�Z
	/// </summary>
	/// <param name="_set"></param>
	void SetVelocity(const VECTOR& _set);

private:
	VECTOR m_position;
	VECTOR m_direction;
	VECTOR m_velocity;
	bool is_UseGravity;


};

