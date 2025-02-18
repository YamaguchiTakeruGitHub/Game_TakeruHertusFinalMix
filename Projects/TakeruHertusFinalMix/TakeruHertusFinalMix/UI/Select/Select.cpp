#include "Select.h"

Select::Select()
	: m_isUpButtonPressed(false)
	, m_isDownButtonPressed(false)
	, m_pushNow(0)
{
}

Select::~Select()
{
}

void Select::Init()
{
	m_isUpButtonPressed = false;
	m_isDownButtonPressed = false;
	m_pushNow = 0;
}

void Select::UpSelect(int& _nowSelect, int _enum, bool isUpButton)
{
	if (isUpButton == true && !m_isUpButtonPressed)
	{
		m_isUpButtonPressed = true;
		_nowSelect = (_nowSelect + (_enum - 1)) % _enum;
		m_pushNow = 1;
	}
	if (!isUpButton)
	{
		m_isUpButtonPressed = false;
	}
}

void Select::DownSelect(int& _nowSelect, int _enum, bool isDownButton)
{
	if (isDownButton == true && !m_isDownButtonPressed)
	{
		m_isDownButtonPressed = true;
		_nowSelect = (_nowSelect + 1) % _enum;
		m_pushNow = 1;
	}
	if (!isDownButton)
	{
		m_isDownButtonPressed = false;
	}
}

void Select::LeftSelect(int& _nowSelect, int _enum, bool isLeftButton)
{
	if (isLeftButton == true && !m_isDownButtonPressed)
	{
		m_isDownButtonPressed = true;
		_nowSelect = (_nowSelect + 1) % _enum;
		m_pushNow = 1;
	}
	if (!isLeftButton)
	{
		m_isDownButtonPressed = false;
	}
}

void Select::RightSelect(int& _nowSelect, int _enum, bool isRightButton)
{
	if (isRightButton == true && !m_isDownButtonPressed)
	{
		m_isDownButtonPressed = true;
		_nowSelect = (_nowSelect + 1) % _enum;
		m_pushNow = 1;
	}
	if (!isRightButton)
	{
		m_isDownButtonPressed = false;
	}
}
