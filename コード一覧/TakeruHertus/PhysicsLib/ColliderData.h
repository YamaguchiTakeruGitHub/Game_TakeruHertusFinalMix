#pragma once
#include <DxLib.h>

/// <summary>
/// “–‚½‚è”»’è‚Ìƒf[ƒ^
/// </summary>
class ColliderData
{
public:

	/// <summary>
	/// “–‚½‚è”»’è‚Ìí—Ş
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
	/// “–‚½‚è”»’è‚Ìí—Ş‚ğæ“¾‚·‚é
	/// </summary>
	/// <returns></returns>
	Kind GetKind() const { return m_kind; }

private:
	Kind m_kind;

};

