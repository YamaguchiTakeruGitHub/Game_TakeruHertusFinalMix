#include "EquipmentMenu.h"
#include <DxLib.h>

EquipmentMenu::EquipmentMenu()
{
}

EquipmentMenu::~EquipmentMenu()
{
}

void EquipmentMenu::Init()
{
}

void EquipmentMenu::Update()
{
}

void EquipmentMenu::Draw()
{
#ifdef _DEBUG

	// 描画ブレンドモードをノーブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

	DrawBox(0, 0, 1280, 740, 0x000000, true);

	// 描画ブレンドモードを加算ブレンド（１００％）にする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	DrawString(10, 10, "EquipmentMenu", 0xffffff, 16);
#endif // _DEBUG

}

void EquipmentMenu::Final()
{
}
