#pragma once
#include "../Base/Component.h"
#include "../../../UI/UIManager.h"
#include "../../../InputDevice/InputDeviceManager.h"

class ComponentComandShortcutSystem : public Component
{
	std::shared_ptr<InputDeviceManager> m_Idm;

	int m_shortcutGraphHandle[4];
	VECTOR m_shortcutGraphPos[4];

	/*コマンドフラグ*/
	bool m_isShortcut1;
	bool m_isShortcut2;
	bool m_isShortcut3;

	/*セレクトシステム変数*/
	bool m_isB_ButtonPressed;
	bool m_isX_ButtonPressed;
	bool m_isY_ButtonPressed;


public:
	ComponentComandShortcutSystem();
	
	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

	void SetIsShortcut1(const bool& _isShortcut1) { m_isShortcut1 = _isShortcut1; }
	bool GetIsShortcut1() const { return m_isShortcut1; }

	void SetIsShortcut2(const bool& _isShortcut2) { m_isShortcut2 = _isShortcut2; }
	bool GetIsShortcut2() const { return m_isShortcut2; }

	void SetIsShortcut3(const bool& _isShortcut3) { m_isShortcut3 = _isShortcut3; }
	bool GetIsShortcut3() const { return m_isShortcut3; }

	
};

