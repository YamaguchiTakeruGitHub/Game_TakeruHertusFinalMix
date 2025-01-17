#include "Rigidbody.h"

Rigidbody::Rigidbody()
	: m_position(VGet(0,0,0))
	, m_direction(VGet(0,0,0))
	, m_velocity(VGet(0,0,0))
	, is_UseGravity(false)
{
}

void Rigidbody::Init(bool _useGravity)
{
	m_position = VGet(0, 0, 0);
	m_direction = VGet(0, 0, 0);
	m_velocity = VGet(0, 0, 0);
	this->is_UseGravity = _useGravity;
}

void Rigidbody::SetVelocity(const VECTOR& _set)
{
	m_velocity = _set;
	if (VSquareSize(m_velocity) > 0)
	{
		m_direction = VNorm(m_velocity);
	}
}

