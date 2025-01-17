#include "CustomizationMenu.h"
#include <DxLib.h>

CustomizationMenu::CustomizationMenu()
{
}

CustomizationMenu::~CustomizationMenu()
{
}

void CustomizationMenu::Init()
{
}

void CustomizationMenu::Update()
{
}

void CustomizationMenu::Draw()
{
#ifdef _DEBUG

	// 描画ブレンドモードをノーブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

	DrawBox(0, 0, 1280, 740, 0x000000, true);

	// 描画ブレンドモードを加算ブレンド（１００％）にする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	DrawString(10, 10, "CustomizationtMenu", 0xffffff, 16);
#endif // _DEBUG
}

void CustomizationMenu::Final()
{
}
