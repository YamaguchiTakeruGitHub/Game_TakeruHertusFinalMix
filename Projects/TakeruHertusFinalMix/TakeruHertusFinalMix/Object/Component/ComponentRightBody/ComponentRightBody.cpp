#include "ComponentRightBody.h"

void ComponentRightBody::Init()
{
}

void ComponentRightBody::Update()
{

	//velocity = VAdd(velocity, VGet(0, GRAVITY, 0));

	//// �ő�d�͉����x���傫��������N�����v
	//if (velocity.y < MAX_GRAVITY_ACCEL)
	//{
	//	velocity = VGet(velocity.x, MAX_GRAVITY_ACCEL, velocity.z);
	//}
	
}

void ComponentRightBody::Draw()
{
}

void ComponentRightBody::Final()
{
}

void ComponentRightBody::NormalizeDirection()
{
	//�����̐��K�����s��
	if (VSquareSize(direction) > 0)
	{
		direction = VNorm(direction);
	}
}
