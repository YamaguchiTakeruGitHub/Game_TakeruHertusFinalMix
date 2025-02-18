#pragma once
#include "../Entity/Entity.h"

class Command : public Entity
{
private:
	std::shared_ptr<ComponentComandSystem> m_comandSystem;
	std::shared_ptr<ComponentComandShortcutSystem> m_shortcutSystem;
	std::shared_ptr<InputDeviceManager> m_Idm;


	bool m_isComandSystem;
	bool m_isShortcutSystem;


public:
	Command();

	void Init();
	void Update();
	void Draw();
	void Final();

	//======================================================================
	// セッターゲッター
	//======================================================================

	void SetIsAttackCommand(const bool& _isAttack) { m_comandSystem->SetIsAttack(_isAttack); }
	bool GetIsAttackCommand() { return m_comandSystem->GetIsAttack(); }

	void SetIsMagic(const bool& _isMagic) { m_comandSystem->SetIsMagic(_isMagic); }
	bool GetIsMagic() { return m_comandSystem->GetIsMagic(); }

	void SetIsItem(const bool& _isItem) { m_comandSystem->SetIsItem(_isItem); }
	bool GetIsItem() { return m_comandSystem->GetIsItem(); }

	void SetIsMenu(const bool& _isMenu) { m_comandSystem->SetIsMenu(_isMenu); }
	bool GetIsMenu() { return m_comandSystem->GetIsMenu(); }

};

