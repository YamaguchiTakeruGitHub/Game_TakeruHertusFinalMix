#include "CharacterIcon.h"

CharacterIcon::CharacterIcon()
	: position(VGet(0,0,0))
	, imgHandle(-1)
{
}

CharacterIcon::~CharacterIcon()
{
}

void CharacterIcon::Init()
{
	position = VGet(1100, 600, 0);
	imgHandle = LoadGraph("../Asset/2D/CharaIcon/playerIcon.png");
}

void CharacterIcon::Update()
{
}

void CharacterIcon::Draw()
{
	DrawCircle(position.x, position.y, 70, 0x000000, true);
	DrawGraph(position.x - 50, position.y - 50,imgHandle, false);
}

void CharacterIcon::Final()
{
	DeleteGraph(imgHandle);
}
