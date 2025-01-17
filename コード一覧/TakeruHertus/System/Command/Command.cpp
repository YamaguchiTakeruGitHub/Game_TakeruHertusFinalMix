#include "Command.h"

Command::Command()
	: pos()
	, is()
	, nowSelect()
	, pushNow()
	, pushBefore()
	, isDUpButtonPressed(false)
	, isDDownButtonPressed(false)
	, commandInterval(10)
	, isBButtonPressed(false)

{
	m_Idm = std::make_shared<InputDeviceManager>();
}

Command::~Command()
{
}

void Command::Init()
{
	m_Idm->Init();

	commandInterval = 10;
	nowSelect = 0;
	pushBefore = 0;
	pushNow = eCommandList_Attack;
	isDUpButtonPressed = false;
	isDDownButtonPressed = false;

	pos.m_AttackSelect = VGet(20.0f, 600.0f, 0.0f);
	pos.m_MagicSelect = VGet(20.0f, 620.0f, 0.0f);
	pos.m_ItemSelect = VGet(20.0f, 640.0f, 0.0f);
	pos.m_kariSelect = VGet(20.0f, 660.0f, 0.0f);
	pos.m_SelectPoint = VGet(5.0f, pos.m_AttackSelect.y, 0.0f);

	is.m_Attack = false;
	is.m_Magic = false;
	is.m_Item = false;
	is.m_kari = false;

	isBButtonPressed = false;
}

void Command::Update()
{
	
	m_Idm->Update();



	if (m_Idm->joyPad->isDUP == true && !isDUpButtonPressed)
	{
		isDUpButtonPressed = true;

		nowSelect = (nowSelect + (eCommandList_Num - 1)) % eCommandList_Num;
		pushNow = 1;
	}
	if (!m_Idm->joyPad->isDUP)
	{
		isDUpButtonPressed = false;
	}


	if (m_Idm->joyPad->isDDOWN == true && !isDDownButtonPressed)
	{
		isDDownButtonPressed = true;
		nowSelect = (nowSelect + 1) % eCommandList_Num;
		pushNow = 1;
	}
	if (!m_Idm->joyPad->isDDOWN)
	{
		isDDownButtonPressed = false;
	}

	

	is.m_Attack = false;
	is.m_Magic = false;
	is.m_Item = false;
	is.m_kari = false;


	if (m_Idm->joyPad->isB == true && !isBButtonPressed)
	{
		isBButtonPressed = true;
		switch (nowSelect)
		{
		case eCommandList_Attack:
			is.m_Attack = true;
			break;

		case eCommandList_Magic:
			is.m_Magic = true;
			break;

		case eCommandList_Item:
			is.m_Item = true;
			break;

		case eCommandList_kari:
			is.m_kari = true;
			break;
		}
	}
	if (!m_Idm->joyPad->isB)
	{
		isBButtonPressed = false;
	}

#ifdef _DEBUG

	switch (nowSelect)
	{
	case eCommandList_Attack:
		pos.m_SelectPoint.y = pos.m_AttackSelect.y;
		break;

	case eCommandList_Magic:
		pos.m_SelectPoint.y = pos.m_MagicSelect.y;
		break;

	case eCommandList_Item:
		pos.m_SelectPoint.y = pos.m_ItemSelect.y;
		break;

	case eCommandList_kari:
		pos.m_SelectPoint.y = pos.m_kariSelect.y;
		break;
	}

#endif
}

void Command::Draw()
{


#ifdef _DEBUG

	DrawFormatString(10, 580, 0xffffff, "COMMAND");
	DrawFormatString(pos.m_SelectPoint.x, pos.m_SelectPoint.y, 0xff0000, "→");

	switch (nowSelect)
	{
	case eCommandList_Attack:
		DrawFormatString(pos.m_AttackSelect.x + commandInterval, pos.m_AttackSelect.y, 0xffffff, "たたかう");

		DrawFormatString(pos.m_MagicSelect.x, pos.m_MagicSelect.y, 0xffffff, "まほう");
		DrawFormatString(pos.m_ItemSelect.x, pos.m_ItemSelect.y, 0xffffff, "アイテム");
		DrawFormatString(pos.m_kariSelect.x, pos.m_kariSelect.y, 0xffffff, "かり");

		break;

	case eCommandList_Magic:
		DrawFormatString(pos.m_MagicSelect.x + commandInterval, pos.m_MagicSelect.y, 0xffffff, "まほう");

		DrawFormatString(pos.m_AttackSelect.x, pos.m_AttackSelect.y, 0xffffff, "たたかう");
		DrawFormatString(pos.m_ItemSelect.x, pos.m_ItemSelect.y, 0xffffff, "あいてむ");
		DrawFormatString(pos.m_kariSelect.x, pos.m_kariSelect.y, 0xffffff, "かり");

		break;

	case eCommandList_Item:
		DrawFormatString(pos.m_ItemSelect.x + commandInterval, pos.m_ItemSelect.y, 0xffffff, "アイテム");

		DrawFormatString(pos.m_AttackSelect.x, pos.m_AttackSelect.y, 0xffffff, "たたかう");
		DrawFormatString(pos.m_MagicSelect.x, pos.m_MagicSelect.y, 0xffffff, "まほう");
		DrawFormatString(pos.m_kariSelect.x, pos.m_kariSelect.y, 0xffffff, "かり");

		break;

	case eCommandList_kari:
		DrawFormatString(pos.m_kariSelect.x + commandInterval, pos.m_kariSelect.y, 0xffffff, "かり");

		DrawFormatString(pos.m_AttackSelect.x, pos.m_AttackSelect.y, 0xffffff, "たたかう");
		DrawFormatString(pos.m_MagicSelect.x, pos.m_MagicSelect.y, 0xffffff, "まほう");
		DrawFormatString(pos.m_ItemSelect.x, pos.m_ItemSelect.y, 0xffffff, "あいてむ");

		break;
	}

	if (is.m_Attack == true)	DrawString(10, 20, "たたかうが押された", 0xffffff, 16);
	if (is.m_Magic == true)		DrawString(10, 20, "魔法が押された", 0xffffff, 16);
	if (is.m_Item == true)		DrawString(10, 20, "アイテムが押された", 0xffffff, 16);
	if (is.m_kari == true)		DrawString(10, 20, "かりが押された", 0xffffff, 16);



#endif


}

void Command::Final()
{
}
