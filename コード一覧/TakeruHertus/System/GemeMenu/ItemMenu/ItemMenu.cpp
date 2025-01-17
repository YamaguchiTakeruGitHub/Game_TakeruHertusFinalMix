#include "ItemMenu.h"
#include <DxLib.h>

ItemMenu::ItemMenu()
	: nowSelect(0)
	, pushNow(0)
	, pushBefore(0)
	, isDUpButtonPressed(false)
	, isDDownButtonPressed(false)
	, isBButtonPressed(false)

	, m_isPlayerSelect(false)
	, m_isBackyardSelect(false)

	, m_SelectPoint(VGet(480, 200, 0))
	, m_playerSelectPos(VGet(500, 200, 0))
	, m_backyardSelectPos(VGet(500, 220, 0))
{
	m_Idm = std::make_shared<InputDeviceManager>();
	m_playerPouch = std::make_shared<PlayerPouch>();
}

ItemMenu::~ItemMenu()
{
}

void ItemMenu::Init()
{
	m_Idm.get()->Init();
	m_playerPouch.get()->Init();

	nowSelect = 0;
	pushNow = 0;
	pushBefore = 0;
	isDUpButtonPressed = false;
	isDDownButtonPressed = false;
	isBButtonPressed = false;

	m_isPlayerSelect = false;
	m_isBackyardSelect = false;

	m_SelectPoint = VGet(480, 200, 0);
	m_playerSelectPos = VGet(500, 200, 0);
	m_backyardSelectPos = VGet(500, 220, 0);

}

void ItemMenu::Update()
{
	m_Idm.get()->Update();

	if (m_isPlayerSelect == false && m_isBackyardSelect == false)
	{
		Selecter();
	}

	

	if (m_Idm->joyPad->isB == true && !isBButtonPressed)
	{
		isBButtonPressed = true;
		
		switch (nowSelect)
		{
		case eItemMenu_Player:
			m_isPlayerSelect = true;
			break;

		case eItemMenu_backyard:
			m_isBackyardSelect = true;
			break;
		}

	}
	if (!m_Idm->joyPad->isB)
	{
		isBButtonPressed = false;
	}

	switch (nowSelect)
	{
	case eItemMenu_Player:
		m_SelectPoint.y = m_playerSelectPos.y;
		break;

	case eItemMenu_backyard:
		m_SelectPoint.y = m_backyardSelectPos.y;
		break;
	}


	if (m_isPlayerSelect == true)
	{
		m_playerPouch.get()->Update();
		if (m_Idm->joyPad->isA == true)
		{
			m_isPlayerSelect = false;
		}
	}

	if (m_isBackyardSelect == true)
	{
		if (m_Idm->joyPad->isA == true)
		{
			m_isBackyardSelect = false;
		}
	}

}

void ItemMenu::Draw()
{
#ifdef _DEBUG

	// 描画ブレンドモードをノーブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

	DrawBox(0, 0, 1280, 740, 0x000000, true);

	// 描画ブレンドモードを加算ブレンド（１００％）にする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	DrawString(10, 10, "ItemMenu", 0xffffff, 16);

	DrawString(m_SelectPoint.x, m_SelectPoint.y, "→", 0xff0000, 16);

	DrawString(m_playerSelectPos.x, m_playerSelectPos.y, "プレイヤーポーチ", 0xffffff, 16);
	DrawString(m_backyardSelectPos.x, m_backyardSelectPos.y, "バックヤード", 0xffffff, 16);
	
	if (m_isPlayerSelect == true ||
		m_isBackyardSelect == true)
	{
		DrawString(m_SelectPoint.x - 20, m_SelectPoint.y, "○", 0xff0000, 16);
	}

	if (m_isPlayerSelect == true)
	{
		m_playerPouch.get()->Draw();
	}

#endif // _DEBUG

}

void ItemMenu::Final()
{

}

void ItemMenu::Selecter()
{
	if (m_Idm->joyPad->isDUP == true && !isDUpButtonPressed)
	{
		isDUpButtonPressed = true;

		nowSelect = (nowSelect + (eItemMenu_Num - 1)) % eItemMenu_Num;
		pushNow = 1;
	}
	if (!m_Idm->joyPad->isDUP)
	{
		isDUpButtonPressed = false;
	}


	if (m_Idm->joyPad->isDDOWN == true && !isDDownButtonPressed)
	{
		isDDownButtonPressed = true;
		nowSelect = (nowSelect + 1) % eItemMenu_Num;
		pushNow = 1;
	}
	if (!m_Idm->joyPad->isDDOWN)
	{
		isDDownButtonPressed = false;
	}
}
