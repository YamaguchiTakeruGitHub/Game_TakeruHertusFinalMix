#include "OneStAvenue.h"

OneStAvenue::OneStAvenue()
	: position(VGet(911.7f,20.0f, -1188.0f))
	, radius(10.0f)
{
}

OneStAvenue::~OneStAvenue()
{
}

void OneStAvenue::Init()
{
	position = VGet(911.7f, 20.0f, -1188.0f);
	radius = 10.0f;
}

void OneStAvenue::Update()
{
	
}

void OneStAvenue::Draw()
{
	DrawSphere3D(position, radius, 5, 0x00ff00, 0x00ff00, false);
}

void OneStAvenue::Fianl()
{
}

bool OneStAvenue::IsHitPosition(VECTOR _pos, float _radius)
{
	auto ppL = VSub(position, _pos);
	auto ppLS = VSize(ppL);
	auto rr = (_radius + radius);

	if (ppLS <= rr)
	{
		return true;
	}

	return false;
}
