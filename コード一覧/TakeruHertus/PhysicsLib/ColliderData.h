#pragma once
#include <DxLib.h>

/// <summary>
/// �����蔻��̃f�[�^
/// </summary>
class ColliderData
{
public:

	/// <summary>
	/// �����蔻��̎��
	/// </summary>
	enum class Kind
	{
		Sphere,
		Capsule,
		AABB,
		OBB,
	};

	ColliderData(Kind _kind) { this->m_kind = _kind; }
	virtual ~ColliderData(){}

	/// <summary>
	/// �����蔻��̎�ނ��擾����
	/// </summary>
	/// <returns></returns>
	Kind GetKind() const { return m_kind; }

private:
	Kind m_kind;

};

