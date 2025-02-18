#include "JoyPad.h"

JoyPad::JoyPad()
	: pad()
	, Pad1(GetJoypadInputState(DX_INPUT_PAD1))
	, count(0)
	, isA(false)
	, isB(false)
	, isX(false)
	, isY(false)
	, isLB(false)
	, isRB(false)
	, isBACK(false)
	, isSTART(false)
	, isSTICKBL(false)
	, isSTICKBR(false)
	, isDUP(false)
	, isDRIGHT(false)
	, isDDOWN(false)
	, isDLEFT(false)

	, isAHold(false)
	, isBHold(false)
	, isXHold(false)
	, isYHold(false)
	, isLBHold(false)
	, isRBHold(false)
	, isBACKHold(false)
	, isSTARTHold(false)
	, isSTICKBLHold(false)
	, isSTICKBRHold(false)

	, isDUPHold(false)	
	, isDRIGHTHold(false)
	, isDDOWNHold(false)
	, isDLEFTHold(false)

	, pisA(false)
	, pisB(false)
	, pisX(false)
	, pisY(false)
	, pisLB(false)
	, pisRB(false)
	, pisBACK(false)
	, pisSTART(false)
	, pisSTICKL(false)
	, pisSTICKR(false)

	, pisDUP(false)
	, pisDRIGHT(false)
	, pisDDOWN(false)
	, pisDLEFT(false)
{
}

JoyPad::~JoyPad()
{
}

void JoyPad::Init()
{


	Pad1 = GetJoypadInputState(DX_INPUT_PAD1);
	count = 0;

	isA = false;
	isB = false;
	isX = false;
	isY = false;
	isLB = false;
	isRB = false;
	isBACK = false;
	isSTART = false;
	isSTICKBL = false;
	isSTICKBR = false;

	isDUP = false;
	isDRIGHT = false;
	isDDOWN = false;
	isDLEFT = false;

	isAHold = false;
	isBHold = false;
	isXHold = false;
	isYHold = false;
	isLBHold = false;
	isRBHold = false;
	isBACKHold = false;
	isSTARTHold = false;
	isSTICKBLHold = false;
	isSTICKBRHold = false;

	isDUPHold = false;
	isDRIGHTHold = false;
	isDDOWNHold = false;
	isDLEFTHold = false;

	pisA = false;
	pisB = false;
	pisX = false;
	pisY = false;
	pisLB = false;
	pisRB = false;
	pisBACK = false;
	pisSTART = false;
	pisSTICKL = false;
	pisSTICKR = false;

	pisDUP = false;
	pisDRIGHT = false;
	pisDDOWN = false;
	pisDLEFT = false;

}

void JoyPad::Update()
{
	GetJoypadDirectInputState(DX_INPUT_PAD1, &pad);

	isA = false;
	isB = false;
	isX = false;
	isY = false;
	isLB = false;
	isRB = false;
	isBACK = false;
	isSTART = false;
	isSTICKBL = false;
	isSTICKBR = false;

	isDUP = false;
	isDRIGHT = false;
	isDDOWN = false;
	isDLEFT = false;

	isAHold = false;
	isBHold = false;
	isXHold = false;
	isYHold = false;
	isLBHold = false;
	isRBHold = false;
	isBACKHold = false;
	isSTARTHold = false;
	isSTICKBLHold = false;
	isSTICKBRHold = false;

	isDUPHold = false;
	isDRIGHTHold = false;
	isDDOWNHold = false;
	isDLEFTHold = false;

	/*ホールドボタン（start）*/

	//Aボタン
	if (pad.Buttons[PadButton::A])
	{
		
		isAHold = true;//別クラスで判定する用のフラグ

	}
	//Bボタン
	if (pad.Buttons[PadButton::B])
	{
		isBHold = true;//別クラスで判定する用のフラグ
	}
	//Yボタン
	if (pad.Buttons[PadButton::Y])
	{
		isYHold = true;//別クラスで判定する用のフラグ
	}
	//Xボタン
	if (pad.Buttons[PadButton::X])
	{
		
		isXHold = true;//別クラスで判定する用のフラグ
	}
	//LBボタン
	if (pad.Buttons[PadButton::LB])
	{
		
		isLBHold = true;//別クラスで判定する用のフラグ
	}
	//RBボタン
	if (pad.Buttons[PadButton::RB])
	{
		isRBHold = true;//別クラスで判定する用のフラグ
	}
	/*ホールドボタン（start）*/

	//Aボタン
	if (pad.Buttons[PadButton::A] && !pisA)
	{
		pisA = true;
		isA = true;//別クラスで判定する用のフラグ

	}
	//Bボタン
	if (pad.Buttons[PadButton::B])
	{
		pisB = true;
		isB = true;//別クラスで判定する用のフラグ
	}
	//Yボタン
	if (pad.Buttons[PadButton::Y])
	{
		pisY = true;
		isY = true;//別クラスで判定する用のフラグ
	}
	//Xボタン
	if (pad.Buttons[PadButton::X])
	{
		pisX = true;
		isX = true;//別クラスで判定する用のフラグ
	}
	//LBボタン
	if (pad.Buttons[PadButton::LB])
	{
		pisLB = true;
		isLB = true;//別クラスで判定する用のフラグ
	}
	//RBボタン
	if (pad.Buttons[PadButton::RB])
	{
		pisRB = true;
		isRB = true;//別クラスで判定する用のフラグ
	}
	//BACKボタン
	if (pad.Buttons[PadButton::BACK])
	{
		pisBACK = true;
		isBACK = true;//別クラスで判定する用のフラグ
	}
	//STARTボタン
	if (pad.Buttons[PadButton::START])
	{
		pisSTART = true;
		isSTART = true;//別クラスで判定する用のフラグ
	}
	//STICKLボタン
	if (pad.Buttons[PadButton::STICKBL])
	{
		pisSTICKL = true;
		isSTICKBL = true;//別クラスで判定する用のフラグ
	}
	//STICKRボタン
	if (pad.Buttons[PadButton::STICKBR])
	{
		pisSTICKR = true;
		isSTICKBR = true;//別クラスで判定する用のフラグ
	}

	//特定のボタンが押されていない時はフラグをおろす
	if (!pad.Buttons[PadButton::A]
		&& !pad.Buttons[PadButton::B]
		&& !pad.Buttons[PadButton::Y]
		&& !pad.Buttons[PadButton::X]
		&& !pad.Buttons[PadButton::LB]
		&& !pad.Buttons[PadButton::RB]
		&& !pad.Buttons[PadButton::BACK]
		&& !pad.Buttons[PadButton::START]
		&& !pad.Buttons[PadButton::STICKBL]
		&& !pad.Buttons[PadButton::STICKBR])
	{
		pisA = false;
		pisA = false;
		pisB = false;
		pisX = false;
		pisY = false;
		pisLB = false;
		pisRB = false;
		pisBACK = false;
		pisSTART = false;
		pisSTICKL = false;
		pisSTICKR = false;

		pisDUP = false;
		pisDRIGHT = false;
		pisDDOWN = false;
		pisDLEFT = false;
	}
	/*ボタン（end）*/

	/*十字キー（start）*/
	switch (pad.POV[PadButton::CROSSKEY])
	{
	case PadButton::DUP://上
		count++;
		isDUP = true;//別クラスで判定する用のフラグ
		break;

	case PadButton::DRIGHT://右
		count = 0;
		isDRIGHT = true;//別クラスで判定する用のフラグ
		break;

	case PadButton::DDOWN://下
		count--;
		isDDOWN = true;//別クラスで判定する用のフラグ
		break;

	case PadButton::DLEFT://左
		count = 1000;
		isDLEFT = true;//別クラスで判定する用のフラグ
		break;

	default:
		break;
	}
	/*十字キー（end）*/
}