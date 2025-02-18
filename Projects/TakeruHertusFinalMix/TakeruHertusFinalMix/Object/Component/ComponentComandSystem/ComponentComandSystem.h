#pragma once
#include "../Base/Component.h"
#include "../../../UI/UIManager.h"
#include "../../../InputDevice/InputDeviceManager.h"

class ComponentComandSystem : public Component
{
private:
	std::shared_ptr<UIManager> m_UI;
	std::shared_ptr<InputDeviceManager> m_Idm;

	int commandGraphHandle[5];
	VECTOR commandGraphPos[5];

	int commandSelectGraphHandle[4];
	VECTOR commandSelectGraphPos[4];

	/*コマンドフラグ*/
	bool m_isAttack;
	bool m_isMagic;
	bool m_isItem;
	bool m_isMenu;


	/*セレクトシステム変数*/
	typedef enum
	{
		eSelect_Attack,
		eSelect_Magic,
		eSelect_Item,
		eSelect_Menu,
		eSelect_Num
	}eSelect;
	int m_nowSelect;
	bool isB_ButtonPressed;
	VECTOR selectPosition;

public:
	ComponentComandSystem();
	~ComponentComandSystem() override;
	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

	void SetIsAttack(const bool& _isAttack) { m_isAttack = _isAttack; }
	bool GetIsAttack() const { return m_isAttack; }

	void SetIsMagic(const bool& _isMagic) { m_isMagic = _isMagic; }
	bool GetIsMagic() const { return m_isMagic; }

	void SetIsItem(const bool& _isItem) { m_isItem = _isItem; }
	bool GetIsItem() const { return m_isItem; }

	void SetIsMenu(const bool& _isMenu) { m_isMenu = _isMenu; }
	bool GetIsMenu() const { return m_isMenu; }

};

