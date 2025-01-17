#include "PlayerPouch.h"

PlayerPouch::PlayerPouch()
	: nowSelect(0)
	, pushNow(0)
	, pushBefore(0)
	, isDUpButtonPressed(false)
	, isDDownButtonPressed(false)
	, isBButtonPressed(false)

	, m_SelectPoint(VGet(700,200,0))
	, m_SetItemPoint_1(VGet(700, 200, 0))
	, m_SetItemPoint_2(VGet(700, 220, 0))
	, m_SetItemPoint_3(VGet(700, 240, 0))

	, m_isSetItem_1(false)
	, m_isSetItem_2(false)
	, m_isSetItem_3(false)
{
	m_Idm = std::make_shared<InputDeviceManager>();
}

PlayerPouch::~PlayerPouch()
{
}

void PlayerPouch::Init()
{
	m_Idm.get()->Init();

	nowSelect = 0;
	pushNow = 0;
	pushBefore = 0;
	isDUpButtonPressed = false;
	isDDownButtonPressed = false;
	isBButtonPressed = false;

	m_SelectPoint = VGet(700, 200, 0);
	m_SetItemPoint_1 = VGet(700, 200, 0);
	m_SetItemPoint_2 = VGet(700, 220, 0);
	m_SetItemPoint_3 = VGet(700, 240, 0);
			
	m_isSetItem_1 = false;
	m_isSetItem_2 = false;
	m_isSetItem_3 = false;
}

void PlayerPouch::Update()
{
	m_Idm.get()->Update();

	
	Selecter();

	m_isSetItem_1 = false;
	m_isSetItem_2 = false;
	m_isSetItem_3 = false;

	if (m_Idm->joyPad->isB == true && !isBButtonPressed)
	{
		isBButtonPressed = true;

		switch (nowSelect)
		{
		case eSetItem_1:
			m_isSetItem_1 = true;
			break;

		case eSetItem_2:
			m_isSetItem_2 = true;
			break;

		case eSetItem_3:
			m_isSetItem_3 = true;
			break;
		}

	}
	if (!m_Idm->joyPad->isB)
	{
		isBButtonPressed = false;
	}

	switch (nowSelect)
	{
	case eSetItem_1:
		m_SelectPoint.y = m_SetItemPoint_1.y;
		break;
	case eSetItem_2:
		m_SelectPoint.y = m_SetItemPoint_2.y;
		break;
	case eSetItem_3:
		m_SelectPoint.y = m_SetItemPoint_3.y;
		break;
	}

}

void PlayerPouch::Draw()
{
#ifdef _DEBUG

	//// •`‰æƒuƒŒƒ“ƒhƒ‚[ƒh‚ðƒm[ƒuƒŒƒ“ƒh‚É‚·‚é
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

	//DrawBox(0, 0, 1280, 740, 0x000000, true);

	//// •`‰æƒuƒŒƒ“ƒhƒ‚[ƒh‚ð‰ÁŽZƒuƒŒƒ“ƒhi‚P‚O‚O“j‚É‚·‚é
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	DrawString(10, 10, "ItemMenu", 0xffffff, 16);

	DrawString(m_SelectPoint.x, m_SelectPoint.y, "¨", 0xff0000, 16);
	
	DrawString(m_SetItemPoint_1.x, m_SetItemPoint_1.y, "SetItem_1", 0xff0000, 16);
	DrawString(m_SetItemPoint_2.x, m_SetItemPoint_2.y, "SetItem_2", 0xff0000, 16);
	DrawString(m_SetItemPoint_3.x, m_SetItemPoint_3.y, "SetItem_3", 0xff0000, 16);

	if (m_isSetItem_1 == true || m_isSetItem_2 == true || m_isSetItem_3 == true)
	{
		DrawString(m_SelectPoint.x - 20, m_SelectPoint.y, "›", 0xff0000, 16);
	}
#endif // _DEBUG
}

void PlayerPouch::Final()
{
}

void PlayerPouch::Selecter()
{
	if (m_Idm->joyPad->isDUP == true && !isDUpButtonPressed)
	{
		isDUpButtonPressed = true;

		nowSelect = (nowSelect + (eSetItem_Num - 1)) % eSetItem_Num;
		pushNow = 1;
	}
	if (!m_Idm->joyPad->isDUP)
	{
		isDUpButtonPressed = false;
	}


	if (m_Idm->joyPad->isDDOWN == true && !isDDownButtonPressed)
	{
		isDDownButtonPressed = true;
		nowSelect = (nowSelect + 1) % eSetItem_Num;
		pushNow = 1;
	}
	if (!m_Idm->joyPad->isDDOWN)
	{
		isDDownButtonPressed = false;
	}
}
