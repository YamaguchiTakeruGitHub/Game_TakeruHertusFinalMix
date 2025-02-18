#include "Player.h"

/*�w�i�@�\�̎��A�߂��Ⴍ����ɂȂ��Ă܂�
* �J�����ƈړ��������o�O���Ƀo�O���Ă���̂Œ��������˂���
*/

Player::Player()
	: comboCount(0)
	, comboTime(0.0f)
	, isCombo(false)
	, rightHandPos(VGet(0,0,0))
	, m_isAttack(false)
	, m_isMagic(false)
	, m_isItem(false)
	, m_isMenu(false)
	, m_rightHandMatrix()
	, m_rightHandPosition()
{
	AddComponent<ComponentRightBody>();
	m_rightBody = GetComponent<ComponentRightBody>();

	AddComponent<ComponentTransform>();
	m_transform = GetComponent<ComponentTransform>();
	
	AddComponent<ComponentModel>();
	m_model = GetComponent<ComponentModel>();

	AddComponent<ComponentCollisionSphere>(m_transform);
	m_sphere = GetComponent<ComponentCollisionSphere>();
	/*AddComponent<ComponentCollisionCapsule>(m_transform);
	m_capsule = GetComponent<ComponentCollisionCapsule>();*/

	//�s��
	AddComponent<ComponentMovement>(m_transform, m_rightBody);
	m_movement = GetComponent<ComponentMovement>();

	AddComponent<ComponentAnimation>(m_model);
	m_animation = GetComponent<ComponentAnimation>();

}

void Player::Init()
{
	Entity::InitComponents();
	//�g�����X�t�H�[���̏����l
	m_transform->position = VGet(0, 2, 0);
	m_transform->scale = VGet(0.4f, 0.4f, 0.4f);

	/*����*/
	m_sphere->radius = 85.0f;

	/*�J�v�Z��*/
	/*m_capsule->radius = 30.0f;
	m_capsule->size = 45.0f;
	m_capsule->minPosition = VSub(m_transform->position, VGet(0, m_capsule->size, 0));
	m_capsule->maxPosition = VAdd(m_transform->position, VGet(0,m_capsule->size,0));*/

	/*���f��*/
	m_model->modelHandle = MV1LoadModel("../Asset/3D/Player/Player.mv1");

	/*�E��*/
	m_rightHandMatrix = MV1GetFrameLocalMatrix(m_model->modelHandle, m_rightHandIndex);
	m_rightHandPosition = MV1GetFramePosition(m_model->modelHandle, m_rightHandIndex);

	/*�R���{*/
	comboCount = 0;
	comboTime = 0.0f;
	isCombo = false;

	/*�R�}���h*/
	m_isAttack = false;
	m_isMagic = false;
	m_isItem = false;
	m_isMenu = false;
}

void Player::Update(float _cHAngle, float _sinParam, float _cosParam)
{

	//�A�j���[�V�����̍X�V
	PlayerAnim();

	//�R���{�̍X�V
	ComboUpdate();
	m_movement->SetConversionHAngle(_cHAngle);
	m_movement->SetConversionCosParam(_cosParam);
	m_movement->SetConversionSinParam(_sinParam);
	Entity::UpdateComponents();//�R���|�[�l���g�̍X�V����
	
	//�J�v�Z���̍X�V
	/*m_capsule->minPosition = VSub(m_transform->position, VGet(0, m_capsule->size, 0));
	m_capsule->maxPosition = VAdd(m_transform->position, VGet(0, m_capsule->size, 0));*/

	//	���W�̍X�V
	MV1SetRotationXYZ(m_model->modelHandle, VGet(0.0, m_movement->GetAngle() / 180.0f * DX_PI_F, 0.0f));
	MV1SetScale(m_model->modelHandle, m_transform->scale);
	MV1SetPosition(m_model->modelHandle, m_transform->position);
}

void Player::Draw()
{
	Entity::DrawComponents();
#ifdef _DEBUG
	if (m_movement->GetIsMove() == true)
	{
		DrawFormatString(0, 40, GetColor(255, 255, 255), "Move");
	}
	else
	{
		DrawFormatString(0, 60, GetColor(255, 255, 255), "Stop");
	}
	DrawFormatString(0, 80, GetColor(255, 255, 255), "comboCount:%d", comboCount);
#endif // _DEBUG
	
}

void Player::Final()
{
	Entity::FinalComponents();
}



void Player::PlayerAnim()
{
	if (m_movement->GetIsMove() == true && m_movement->GetIsGround() == true)
	{
		/*�A�j���[�V��������*/
		//m_animation->PlayBlendAnim(8);
		m_animation->PlayAnim(8);
	}
	else
	{
		//m_animation->PlayBlendAnim(4);
		m_animation->PlayAnim(4);
	}

	if (m_movement->GetISAboidance() == true)
	{
		m_animation->PlayAnim(7);
	}

	if (m_movement->GetIsGround() == false)
	{
		m_animation->PlayAnim(6);
	}

}

void Player::StartCombo()
{
	comboCount++;
	comboTime = COMBODURATION;
	m_animation->ResetAnimationNowTime();
}

void Player::UpdateCombo()
{
	if (comboTime > 0.0f)
	{
		isCombo = true;
		comboTime -= 0.1f;
		if (comboTime <= 0.0f)
		{
			ResetCombo();
		}
	}
}

void Player::ResetCombo()
{
	comboCount = 0;
	comboTime = 0.0f;
	m_animation->ResetAnimationNowTime();//�A�j���[�V�����̍Đ����Ԃ����Z�b�g����

}

void Player::ComboUpdate()
{
	int currentComboCount = comboCount;

	//�U���R�}���h
	if (m_isAttack == true)
	{
		StartCombo();
	}

	UpdateCombo();

	if (comboCount >= 1)
	{
		m_movement->SetIsAtack(true);
	}
	if (comboCount == 0)
	{
		m_movement->SetIsAtack(false);
	}

	if (comboCount == 1)
	{
		m_animation->PlayAnim(0);
		m_movement->SetComboCount(1);
	}
	if (comboCount == 2)
	{
		m_animation->PlayAnim(1);
		m_movement->SetComboCount(2);

	}
	if (comboCount == 3)
	{
		m_animation->PlayAnim(2);
		m_movement->SetComboCount(3);

	}
	if (comboCount == 4)
	{
		m_animation->PlayAnim(3);
		m_movement->SetComboCount(4);

	}
	if (comboCount >= 5)
	{
		comboCount = 0;
		m_movement->SetComboCount(0);
	}
}
