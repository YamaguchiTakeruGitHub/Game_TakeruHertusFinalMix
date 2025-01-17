#pragma once
#include <DxLib.h>
#include <memory>
#include "../../InputDevice/InputDeviceManager.h"


class Command
{
public:
	Command();
	~Command();

	void Init();
	void Update();
	void Draw();
	void Final();


	bool GetIsAttack() const { return is.m_Attack; }
	bool GetIsMagic() const { return is.m_Magic; }
	bool GetIsItem() const { return is.m_Item; }
	bool GetIsKari() const { return is.m_kari; }
	bool GetIsReaction() const { return is.m_Reaction; }

	void SetIsAttack(const bool& newIsAttack) { is.m_Attack = newIsAttack; }
	void SetIsMagic(const bool& newIsMagic) { is.m_Magic = newIsMagic; }
	void SetIsItem(const bool& newIsItem) { is.m_Item = newIsItem; }
	void SetIsKari(const bool& newIsKari) { is.m_kari = newIsKari; }
	void SetIsReaction(const bool& newIsReaction) { is.m_Reaction = newIsReaction; }



private:
	std::shared_ptr<InputDeviceManager> m_Idm;
	

	int commandInterval = 10;   

	int nowSelect;				
	int pushNow;				
	int pushBefore;				

	bool isDUpButtonPressed;	
	bool isDDownButtonPressed;

	bool isBButtonPressed;

	




	
	struct Flag
	{
	public:
		bool m_Attack;	
		bool m_Magic;	
		bool m_Item;	
		bool m_kari;	

		bool m_Reaction;
	}is;






	struct Pos
	{
	public:
		VECTOR m_AttackSelect;	
		VECTOR m_MagicSelect;	
		VECTOR m_ItemSelect;	
		VECTOR m_kariSelect;	
		VECTOR m_SelectPoint;

		VECTOR m_ReactionSelect;
	}pos;

	
	typedef enum
	{
		eCommandList_Attack,
		eCommandList_Magic,
		eCommandList_Item,
		eCommandList_kari,
		//eCommandList_Reaction,

		eCommandList_Num

	}eCommandList;

	

};

