#pragma once
#include <memory>
#include "../../../InputDevice/InputDeviceManager.h"

class PlayerPouch
{
public:
	PlayerPouch();
	~PlayerPouch();

	void Init();
	void Update();
	void Draw();
	void Final();

private:

	void Selecter();

	std::shared_ptr<InputDeviceManager> m_Idm;

	typedef enum
	{
		eSetItem_1,
		eSetItem_2,
		eSetItem_3,

		eSetItem_Num,

	}eSetItem;

	int nowSelect;
	int pushNow;
	int pushBefore;
	bool isDUpButtonPressed;
	bool isDDownButtonPressed;
	bool isBButtonPressed;

	VECTOR m_SelectPoint;
	VECTOR m_SetItemPoint_1;
	VECTOR m_SetItemPoint_2;
	VECTOR m_SetItemPoint_3;

	bool m_isSetItem_1;
	bool m_isSetItem_2;
	bool m_isSetItem_3;

};

