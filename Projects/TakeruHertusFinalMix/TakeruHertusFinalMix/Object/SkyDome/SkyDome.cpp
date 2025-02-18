#include "SkyDome.h"

SkyDome::SkyDome()
{
	AddComponent<ComponentTransform>();
	m_transform = GetComponent<ComponentTransform>();

	AddComponent<ComponentModel>();
	m_model = GetComponent<ComponentModel>();

	time = 0;
}

void SkyDome::Init()
{
	Entity::InitComponents();

	m_transform->position = VGet(0, -800, 0);
	m_transform->scale = VGet(20.0f, 20.0f, 20.0f);
	m_model->LoadModel(". ./Asset/3D/SkyDome/Tutorial/tutorialSkyDome.mv1");

	//�����`���[�g���A���}�b�v�̏ꍇ�͂��̃p�X���i�[
	//if(�`���[�g���A���}�b�v == true)
	// {
	//		LoadModel("�`���[�g���A���}�b�v�p�X")
	// }
	// 
	// if(�Q�[���}�b�v == true)
	// {
	//		LoadModel("�Q�[���}�b�v�p�X")
	// }
	// 
	//�����Q�[���}�b�v�̏ꍇ�͂��̃p�X���i�[

	time = 0;
}

void SkyDome::Update()
{
	Entity::UpdateComponents();

	if (time <= 460)
	{
		time++;
	}
	else
	{
		time = 0;
	}



	MV1SetScale(m_model->modelHandle, m_transform->scale);
	MV1SetPosition(m_model->modelHandle, m_transform->position);
}

void SkyDome::Draw()
{
	Entity::DrawComponents();
}

void SkyDome::Final()
{
	Entity::FinalComponents();
}
