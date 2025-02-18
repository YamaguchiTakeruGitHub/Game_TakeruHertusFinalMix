#include "UIManager.h"

UIManager::UIManager()
{
	m_select = std::make_shared<Select>();
}

UIManager::~UIManager()
{
}

void UIManager::Init()
{
	m_select.get()->Init();
}

