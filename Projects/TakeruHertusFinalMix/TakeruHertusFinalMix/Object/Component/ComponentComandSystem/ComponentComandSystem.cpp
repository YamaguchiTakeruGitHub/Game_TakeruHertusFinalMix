#include "ComponentComandSystem.h"

ComponentComandSystem::ComponentComandSystem()

	/*�I�����Ă��Ȃ��R�}���h�̉摜�ƍ��W����̂��*/
	: commandGraphHandle{ -1, -1, -1, -1, -1 }
	, commandGraphPos{ VGet(0, 0, 0), VGet(0, 0, 0), VGet(0, 0, 0), VGet(0, 0, 0), VGet(0,0,0)}
	
	/*�I�����Ă���R�}���h�̉摜�ƍ��W*/
	, commandSelectGraphHandle{ -1, -1, -1, -1 }
	, commandSelectGraphPos{ VGet(0, 0, 0), VGet(0, 0, 0), VGet(0, 0, 0), VGet(0, 0, 0) }

	/*�R�}���h�t���O*/
	, m_isAttack(false)
	, m_isMagic(false)
	, m_isItem(false)
	, m_isMenu(false)

	/*�Z���N�g�V�X�e���ϐ�*/
	, m_nowSelect(eSelect_Attack)
	, isB_ButtonPressed(false)

	/*�I�𒆂̍��W*/
	, selectPosition(VGet(0, 0, 0))
{
	m_Idm = std::make_shared<InputDeviceManager>();
	m_UI = std::make_shared<UIManager>();
}

ComponentComandSystem::~ComponentComandSystem()
{
	for (int i = 0; i < 4; i++)//�x�N�^�[�ɂ��邩���z��ɂ��邩
	{
		if (commandGraphHandle[i] != -1)
		{
			DeleteGraph(commandGraphHandle[i]);
		}
	}
}

void ComponentComandSystem::Init()
{
	m_Idm->Init();
	

	SetUseASyncLoadFlag(true);
	/*�I�����Ă��Ȃ����̃R�}���h����̂��*/
	commandGraphHandle[0] = LoadGraph("../Asset/2D/Command/UI_Attack.png");//�U��
	commandGraphHandle[1] = LoadGraph("../Asset/2D/Command/UI_Majick.png");//���@
	commandGraphHandle[2] = LoadGraph("../Asset/2D/Command/UI_Item.png");//�A�C�e��
	commandGraphHandle[3] = LoadGraph("../Asset/2D/Command/UI_Menu.png");//���j��
	commandGraphHandle[4] = LoadGraph("../Asset/2D/Command/UI_Comand.png");//�R�}���h�̏�̂��
	SetUseASyncLoadFlag(false);

	commandGraphPos[0] = VGet(20, 546, 0);//�U��
	commandGraphPos[1] = VGet(20, 592, 0);//���@
	commandGraphPos[2] = VGet(20, 638, 0);//�A�C�e��
	commandGraphPos[3] = VGet(20, 684, 0);//���j��
	commandGraphPos[4] = VGet(20, 500, 0);//�R�}���h�̏�̂��
	
	SetUseASyncLoadFlag(true);
	/*�I�����Ă��鎞�̃R�}���h*/
	commandSelectGraphHandle[0] = LoadGraph("../Asset/2D/Command/UI_S_Attack.png");//�U��
	commandSelectGraphHandle[1] = LoadGraph("../Asset/2D/Command/UI_S_Majick.png");//���@
	commandSelectGraphHandle[2] = LoadGraph("../Asset/2D/Command/UI_S_Item.png");//�A�C�e��
	commandSelectGraphHandle[3] = LoadGraph("../Asset/2D/Command/UI_S_Menu.png");//���j��
	SetUseASyncLoadFlag(false);

	commandSelectGraphPos[0] = VGet(40, 546, 0);//�U��
	commandSelectGraphPos[1] = VGet(40, 592, 0);//���@
	commandSelectGraphPos[2] = VGet(40, 638, 0);//�A�C�e��
	commandSelectGraphPos[3] = VGet(40, 684, 0);//���j��

	
	/*�R�}���h�t���O*/
	m_isAttack = false;
	m_isMagic = false;
	m_isItem = false;
	m_isMenu = false;

	/*�Z���N�g�V�X�e���ϐ�*/
	m_nowSelect = eSelect_Attack;
	isB_ButtonPressed = false;

	/*�I�𒆂̍��W*/
	selectPosition = VGet(0, 0, 0);
}

void ComponentComandSystem::Update()
{
	/*�R�}���h�t���O����ɂ��낷*/
	m_isAttack = false;
	m_isMagic = false;
	m_isItem = false;
	m_isMenu = false;

	/*���̓f�o�C�X�̍X�V*/
	m_Idm->Update();

	/*�Z���N�g�V�X�e��*/
	m_UI->m_select->UpSelect(m_nowSelect, eSelect_Num, m_Idm->joyPad->isDUP == true);
	m_UI->m_select->DownSelect(m_nowSelect, eSelect_Num, m_Idm->joyPad->isDDOWN == true);


	/*�R�}���h�I��*/
	if (m_Idm->joyPad->isB == true && !isB_ButtonPressed)
	{
		isB_ButtonPressed = true;
		switch (m_nowSelect)
		{
		case eSelect_Attack:
			m_isAttack = true;
			break;
		case eSelect_Magic:
			m_isMagic = true;
			break;
		case eSelect_Item:
			m_isItem = true;
			break;
		case eSelect_Menu:
			m_isMenu = true;
			break;
		}
	}
	if (!m_Idm->joyPad->isB)
	{
		isB_ButtonPressed = false;
	}
	

}

void ComponentComandSystem::Draw()
{
	DrawGraph(commandGraphPos[4].x, commandGraphPos[4].y, commandGraphHandle[4], true);//��̂��

	switch (m_nowSelect)
	{
	case eSelect_Attack:
		DrawGraph(commandGraphPos[0].x + 20, commandGraphPos[0].y, commandSelectGraphHandle[0], true);


		DrawGraph(commandGraphPos[1].x, commandGraphPos[1].y, commandGraphHandle[1], true);
		DrawGraph(commandGraphPos[2].x, commandGraphPos[2].y, commandGraphHandle[2], true);
		DrawGraph(commandGraphPos[3].x, commandGraphPos[3].y, commandGraphHandle[3], true);
		break;
	case eSelect_Magic:
		DrawGraph(commandGraphPos[1].x + 20, commandGraphPos[1].y, commandSelectGraphHandle[1], true);

		DrawGraph(commandGraphPos[0].x, commandGraphPos[0].y, commandGraphHandle[0], true);
		DrawGraph(commandGraphPos[2].x, commandGraphPos[2].y, commandGraphHandle[2], true);
		DrawGraph(commandGraphPos[3].x, commandGraphPos[3].y, commandGraphHandle[3], true);
		break;

	case eSelect_Item:
		DrawGraph(commandGraphPos[2].x + 20, commandGraphPos[2].y, commandSelectGraphHandle[2], true);

		DrawGraph(commandGraphPos[0].x, commandGraphPos[0].y, commandGraphHandle[0], true);
		DrawGraph(commandGraphPos[1].x, commandGraphPos[1].y, commandGraphHandle[1], true);
		DrawGraph(commandGraphPos[3].x, commandGraphPos[3].y, commandGraphHandle[3], true);
		break;

	case eSelect_Menu:
		DrawGraph(commandGraphPos[3].x + 20, commandGraphPos[3].y, commandSelectGraphHandle[3], true);

		DrawGraph(commandGraphPos[0].x, commandGraphPos[0].y, commandGraphHandle[0], true);
		DrawGraph(commandGraphPos[1].x, commandGraphPos[1].y, commandGraphHandle[1], true);
		DrawGraph(commandGraphPos[2].x, commandGraphPos[2].y, commandGraphHandle[2], true);
		break;
	}
}

void ComponentComandSystem::Final()
{
	for (int i = 0; i < 5; i++)
	{
		if (commandGraphHandle[i] != -1)
		{
			DeleteGraph(commandGraphHandle[i]);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (commandSelectGraphHandle[i] != -1)
		{
			DeleteGraph(commandSelectGraphHandle[i]);
		}
	}
}

