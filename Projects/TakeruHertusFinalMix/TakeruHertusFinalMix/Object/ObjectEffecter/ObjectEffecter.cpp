#include "ObjectEffecter.h"


ObjectEffecter::ObjectEffecter()
	: m_tag("")
{
	AddComponent<ComponentEffect>();
	m_effect = GetComponent<ComponentEffect>();
}

ObjectEffecter::~ObjectEffecter()
{
}


void ObjectEffecter::Init()
{
	Entity::InitComponents();
}

void ObjectEffecter::Update()
{
	Entity::UpdateComponents();
	if (m_tag == "AllStopEffect")
	{
		m_effect->SetEffectTime(0);
		m_effect->SetStopEffect(0);
		m_effect->SetStopEffect(1);
		m_effect->SetStopEffect(5);

	}


	if (m_tag == "TutorialEffectSection_1")
	{
		m_effect->Update_Section1_Event();
		/*m_effect->SetStopEffect(1);*/
	}

	if (m_tag == "TutorialEffectSection_2LeftWeponSelect")
	{
		m_effect->Update_Section2_WeponSelectLeft();
		/*m_effect->SetStopEffect(0);*/
	}

	if (m_tag == "TutorialEffectSection_4Event_1")
	{
		m_effect->Update_section4_WeponGetEvent();
		/*m_effect->SetStopEffect(1);
		m_effect->SetStopEffect(0);*/
	}

	if (m_tag == "TutorialEffectSection_4EnemySpown")
	{
		m_effect->Update_section4_EnemySpown();
		m_effect->SetPosition(VGet(0,0,0), 6);
		/*m_effect->SetStopEffect(1);
		m_effect->SetStopEffect(0);
		m_effect->SetStopEffect(5);*/
	}

	if (m_tag == "SavePoint")
	{
		m_effect->Update_SavePoint();
	}

	if (m_tag == "EnemySpown")
	{
		m_effect->Update_EnemySpown();
	}

}


void ObjectEffecter::Draw()
{
	Entity::DrawComponents();
}

void ObjectEffecter::Final()
{
	Entity::FinalComponents();
}