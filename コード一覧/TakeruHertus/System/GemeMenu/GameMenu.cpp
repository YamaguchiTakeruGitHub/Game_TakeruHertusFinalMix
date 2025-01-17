#include "GameMenu.h"

GameMenu::GameMenu()
	: m_MenuItem(VGet(500, 200, 0))
	, m_MenuEquipment(VGet(500, 220, 0))
	, m_MenuAbility(VGet(500, 240, 0))
	, m_Customization(VGet(500, 260, 0))
	, m_MenuSelect(VGet(480, 200, 0))
	, m_isMenuSelect(false)
	, m_isMenuItem(false)
	, m_isMenuEquipment(false)
	, m_isMenuAbility(false)
	, m_isMenuCustomization(false)
	, m_isMenu(false)
	, m_isCurrentMenu(false)
	, pushNow(0)
	, nowSelect(eMenu_Item)
{
	m_Idm = std::make_shared<InputDeviceManager>();
	m_Menu_Ability = std::make_shared<AbilityMenu>();
	m_Menu_Customization = std::make_shared<CustomizationMenu>();
	m_Menu_Equipment = std::make_shared<EquipmentMenu>();
	m_Menu_Item = std::make_shared<ItemMenu>();
}

GameMenu::~GameMenu()
{
}

void GameMenu::Init()
{
	m_Idm.get()->Init();

	m_MenuSelect = VGet(480, 200, 0);
	m_MenuItem = VGet(500,200,0);
	m_MenuEquipment = VGet(500,220,0);
	m_MenuAbility = VGet(500,240,0);
	m_Customization = VGet(500,260,0);
	m_isMenuSelect = false;
	m_isMenuItem = false;
	m_isMenuEquipment = false;
	m_isMenuAbility = false;
	m_isMenuCustomization = false;
	m_isMenu = false;

	pushNow = 0;
	nowSelect = eMenu_Item;
}

void GameMenu::Update()
{
	m_Idm.get()->Update();

	/*m_isMenuSelect = false;
	m_isMenuItem = false;
	m_isMenuEquipment = false;
	m_isMenuAbility = false;
	m_isMenuCustomization = false;
	m_isCurrentMenu = false;*/

	if (m_isMenuSelect == false ||
		m_isMenuItem == false ||
		m_isMenuEquipment == false ||
		m_isMenuAbility == false ||
		m_isMenuCustomization == false)
	{
		m_isMenu = true;
	}
	else
	{
		m_isMenu = false;
	}

	m_isMenu = m_isCurrentMenu;

	if (m_isMenuItem == false && m_isMenuEquipment == false &&
		m_isMenuAbility == false && m_isMenuCustomization == false)
	{
		//十字キーで項目の変更
		Selecter();
	}

	if (m_Idm->joyPad->isB == true && !isBButtonPressed)
	{
		isBButtonPressed = true;
		switch (nowSelect)
		{
		case eMenu_Item:
			m_isMenuItem = true;
			break;

		case eMenu_Equipment:
			m_isMenuEquipment = true;
			break;

		case eMenu_Ability:
			m_isMenuAbility = true;
			break;

		case eMenu_Customization:
			m_isMenuCustomization = true;
			break;
		}

	}
	if (!m_Idm->joyPad->isB)
	{
		isBButtonPressed = false;
	}

	switch (nowSelect)
	{
	case eMenu_Item:
		m_MenuSelect.y = m_MenuItem.y;
		break;

	case eMenu_Equipment:
		m_MenuSelect.y = m_MenuEquipment.y;
		break;

	case eMenu_Ability:
		m_MenuSelect.y = m_MenuAbility.y;
		break;

	case eMenu_Customization:
		m_MenuSelect.y = m_Customization.y;
		break;
	}
		

		if (m_isMenuItem == true)
		{
			m_Menu_Item.get()->Update();
			if (m_Idm->joyPad->isA == true)
			{
				m_isMenuItem = false;
			}
		}
		if (m_isMenuEquipment == true)
		{
			if (m_Idm->joyPad->isA == true)
			{
				m_isMenuEquipment = false;
			}
		}
		if (m_isMenuAbility == true)
		{
			if (m_Idm->joyPad->isA == true)
			{
				m_isMenuAbility = false;
			}
		}
		if (m_isMenuCustomization == true)
		{
			if (m_Idm->joyPad->isA == true)
			{
				m_isMenuCustomization = false;
			}
		}

	
}

void GameMenu::Draw()
{
#ifdef _DEBUG

	if (m_isMenuItem == false && m_isMenuEquipment == false &&
		m_isMenuAbility == false && m_isMenuCustomization == false)
	{


		// 描画ブレンドモードをノーブレンドにする
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

		DrawBox(0, 0, 1280, 740, 0x000000, true);

		// 描画ブレンドモードを加算ブレンド（１００％）にする
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);


		DrawString(10, 10, "OpneMenu", 0xffffff, 16);
		DrawString(m_MenuSelect.x, m_MenuSelect.y, "→", 0xff0000, 16);

		DrawString(m_MenuItem.x, m_MenuItem.y, "アイテム", 0xffffff, 16);
		DrawString(m_MenuEquipment.x, m_MenuEquipment.y, "そうび", 0xffffff, 16);
		DrawString(m_MenuAbility.x, m_MenuAbility.y, "アビリティ", 0xffffff, 16);
		DrawString(m_Customization.x, m_Customization.y, "カスタマイズ", 0xffffff, 16);

		if (m_isMenuSelect == true ||
			m_isMenuItem == true ||
			m_isMenuEquipment == true ||
			m_isMenuAbility == true ||
			m_isMenuCustomization == true)
		{
			DrawString(m_MenuSelect.x - 20, m_MenuSelect.y, "○", 0xff0000, 16);

		}
	}

	//アイテムメニュー
	if (m_isMenuItem == true)
	{
		m_Menu_Item.get()->Draw();
	}

	//装備メニュー
	if (m_isMenuEquipment == true)
	{
		m_Menu_Equipment.get()->Draw();
	}

	//アビリティメニュー
	if (m_isMenuAbility == true)
	{
		m_Menu_Ability.get()->Draw();
	}

	//カスタマイズメニュー
	if (m_isMenuCustomization == true)
	{
		m_Menu_Customization.get()->Draw();
	}


#endif // _DEBUG
}

void GameMenu::Final()
{
}

void GameMenu::Selecter()
{
	if (m_Idm->joyPad->isDUP == true && !isDUpButtonPressed)
	{
		isDUpButtonPressed = true;

		nowSelect = (nowSelect + (eMenu_Num - 1)) % eMenu_Num;
		pushNow = 1;
	}
	if (!m_Idm->joyPad->isDUP)
	{
		isDUpButtonPressed = false;
	}


	if (m_Idm->joyPad->isDDOWN == true && !isDDownButtonPressed)
	{
		isDDownButtonPressed = true;
		nowSelect = (nowSelect + 1) % eMenu_Num;
		pushNow = 1;
	}
	if (!m_Idm->joyPad->isDDOWN)
	{
		isDDownButtonPressed = false;
	}

}
