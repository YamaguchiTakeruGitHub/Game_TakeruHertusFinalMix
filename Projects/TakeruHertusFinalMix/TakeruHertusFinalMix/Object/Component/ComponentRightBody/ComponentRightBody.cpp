#include "ComponentRightBody.h"

void ComponentRightBody::Init()
{
}

void ComponentRightBody::Update()
{

	//velocity = VAdd(velocity, VGet(0, GRAVITY, 0));

	//// 最大重力加速度より大きかったらクランプ
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
	//向きの正規化を行う
	if (VSquareSize(direction) > 0)
	{
		direction = VNorm(direction);
	}
}
