#include "AbilityMenu.h"
#include <DxLib.h>

AbilityMenu::AbilityMenu()
{
}

AbilityMenu::~AbilityMenu()
{
}

void AbilityMenu::Init()
{
}

void AbilityMenu::Update()
{
}

void AbilityMenu::Draw()
{
#ifdef _DEBUG

	// �`��u�����h���[�h���m�[�u�����h�ɂ���
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

	DrawBox(0, 0, 1280, 740, 0x000000, true);

	// �`��u�����h���[�h�����Z�u�����h�i�P�O�O���j�ɂ���
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	DrawString(10, 10, "AbilityMenu", 0xffffff, 16);
#endif // _DEBUG
}

void AbilityMenu::Final()
{
}
