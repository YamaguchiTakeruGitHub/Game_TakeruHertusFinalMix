#pragma once
#include <DxLib.h>
#include <memory>
#include "../../InputDevice/InputDeviceManager.h"
#include "GameMenuCommon.h"

class GameMenu
{
public:
	GameMenu();
	~GameMenu();

	void Init();
	void Update();
	void Draw();
	void Final();

private:
	void Selecter();


	std::shared_ptr<InputDeviceManager> m_Idm;
	std::shared_ptr<AbilityMenu> m_Menu_Ability;
	std::shared_ptr<CustomizationMenu> m_Menu_Customization;
	std::shared_ptr<EquipmentMenu> m_Menu_Equipment;
	std::shared_ptr<ItemMenu> m_Menu_Item;

	bool m_isMenuSelect;
	bool m_isMenuItem;
	bool m_isMenuEquipment;
	bool m_isMenuAbility;
	bool m_isMenuCustomization;
	bool m_isMenu;
	bool m_isCurrentMenu;

	typedef enum
	{
		eMenu_Item,
		eMenu_Equipment,
		eMenu_Ability,
		eMenu_Customization,

		eMenu_Num

	}eMenu;

	VECTOR m_MenuSelect;
	VECTOR m_MenuItem;
	VECTOR m_MenuEquipment;
	VECTOR m_MenuAbility;
	VECTOR m_Customization;

	int nowSelect;
	int pushNow;
	int pushBefore;

	bool isDUpButtonPressed;
	bool isDDownButtonPressed;

	bool isBButtonPressed;


};

