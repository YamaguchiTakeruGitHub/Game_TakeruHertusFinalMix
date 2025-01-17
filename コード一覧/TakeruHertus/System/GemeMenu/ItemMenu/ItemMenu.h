#pragma once
#include "../../../InputDevice/InputDeviceManager.h"
#include <memory>
#include "PlayerPouch.h"

class ItemMenu
{
public:
	ItemMenu();
	~ItemMenu();

	void Init();
	void Update();
	void Draw();
	void Final();

private:

	void Selecter();

	std::shared_ptr<InputDeviceManager> m_Idm;
	std::shared_ptr<PlayerPouch> m_playerPouch;

	typedef enum
	{
		eItemMenu_Player,
		eItemMenu_backyard,

		eItemMenu_Num,

	}eItemMenu;

	int nowSelect;
	int pushNow;
	int pushBefore;
	bool isDUpButtonPressed;
	bool isDDownButtonPressed;
	bool isBButtonPressed;

	VECTOR m_SelectPoint;
	VECTOR m_playerSelectPos;
	VECTOR m_backyardSelectPos;


	bool m_isPlayerSelect;
	bool m_isBackyardSelect;
};

