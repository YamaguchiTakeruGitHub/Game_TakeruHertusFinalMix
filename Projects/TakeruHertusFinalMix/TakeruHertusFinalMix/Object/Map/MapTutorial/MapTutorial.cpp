#include "MapTutorial.h"
#include <filesystem>
#include <iostream>
#include "../../../CSVLib/CsvData_Reading_And_Writing_Equipment.h"

MapTutorial::MapTutorial()
	: m_Section_2_Object_FoundationModelHandle{-1,-1,-1}
	, m_Section_2_Object_FoundationPosition{VGet(0,0,0), VGet(0,0,0), VGet(0,0,0)}
	, m_section_2_Time(0)
	, m_section_2_MaxTime(0)
	, m_isSection_2(false)
	, m_tag("")
{
	AddComponent<ComponentTransform>();
	m_transform = GetComponent<ComponentTransform>();

	AddComponent<ComponentModel>();
	m_model = GetComponent<ComponentModel>();

	AddComponent<ComponentCollisionPolygon>(m_model);
	m_polygon = GetComponent<ComponentCollisionPolygon>();
}

void MapTutorial::Init()
{
	Entity::InitComponents();
	m_transform->position = VGet(0, 0, 0);
	m_tag = "";

	//モデルのロード
	m_model->LoadModel("../Asset/3D/Map/Tutorial/mapTutorial1Stage.mv1");

	//メッシュ関連
	MV1SetupReferenceMesh(m_model->modelHandle, -1, true);

	m_polygon->polygonList = MV1GetReferenceMesh(m_model->modelHandle, -1, true);

	MV1SetPosition(m_model->modelHandle, m_transform->position);

	//パスを０番目に格納
	m_Section_2_Object_FoundationModelHandle[0] = MV1LoadModel("../Asset/3D/Map/Tutorial/Obj/Section2_Object_Foundation/Section_2_Objct_Foundation.mv1");
	
	//同じデータを使用するモデルハンドルを２つ作成する
	for (int i = 0; i < 2; i++)
	{
		m_Section_2_Object_FoundationModelHandle[i + 1] = MV1DuplicateModel(m_Section_2_Object_FoundationModelHandle[0]);
	}
	m_Section_2_Object_FoundationPosition[0] = VGet(-700, -100, 700);
	m_Section_2_Object_FoundationPosition[1] = VGet(0, -100, 1400);
	m_Section_2_Object_FoundationPosition[2] = VGet(700, -100, 700);
	m_section_2_Time = 0;

	std::string filename = "../GameData/EventData/EventData_TutorialSection.csv";
	std::vector<std::vector<std::string>> data = CSVLib::ReadCSV(filename);
	m_section_2_MaxTime = CSVLib::GetCell_float(data,3,3);

}

void MapTutorial::Update()
{
	Entity::UpdateComponents();

	/*セクション２*/
	if (m_isSection_2 == true)
	{
		if (m_section_2_Time >= m_section_2_MaxTime)
		{
			m_section_2_Time = m_section_2_MaxTime;
		}
		else
		{
			m_section_2_Time++;
		}
		

		if (m_section_2_Time <= m_section_2_MaxTime / 3)
		{
			m_Section_2_Object_FoundationPosition[0].y++;
		}
		if (m_section_2_Time >= m_section_2_MaxTime / 3 && m_section_2_Time <= (m_section_2_MaxTime / 3) * 2)
		{
			m_Section_2_Object_FoundationPosition[1].y++;
		}
		if (m_section_2_Time >= (m_section_2_MaxTime / 3) * 2 && m_section_2_Time <= m_section_2_MaxTime)
		{
			m_Section_2_Object_FoundationPosition[2].y++;
		}

		
		for (int i = 0; i < 3; i++)
		{
			if (m_Section_2_Object_FoundationPosition[i].y >= 0.0f)
			{
				m_Section_2_Object_FoundationPosition[i].y = 0.0f;
			}
		}

		MV1SetPosition(m_Section_2_Object_FoundationModelHandle[0], m_Section_2_Object_FoundationPosition[0]);
		MV1SetPosition(m_Section_2_Object_FoundationModelHandle[1], m_Section_2_Object_FoundationPosition[1]);
		MV1SetPosition(m_Section_2_Object_FoundationModelHandle[2], m_Section_2_Object_FoundationPosition[2]);
		

		
	}
	/*セクション２*/

	if (m_isSection_4 == true)
	{
		m_Section_2_Object_FoundationPosition[0] = VGet(-700, -100, 700);
		m_Section_2_Object_FoundationPosition[1] = VGet(0, -100, 1400);
		m_Section_2_Object_FoundationPosition[2] = VGet(700, -100, 700);
	}

}

void MapTutorial::Draw()
{
	Entity::DrawComponents();

	if (m_tag == "Foundation")
	{
		if (m_isSection_2 == true)
		{
			for (int i = 0; i < 3; i++)
			{
				MV1DrawModel(m_Section_2_Object_FoundationModelHandle[i]);
			}
		}
	}
}

void MapTutorial::Final()
{
	Entity::FinalComponents();
	
	for (int i = 0; i < 3; i++)
	{
		if (m_Section_2_Object_FoundationModelHandle[i] != -1)
		{
			MV1DeleteModel(m_Section_2_Object_FoundationModelHandle[i]);
		}
	}
}

int MapTutorial::GetFoundationModelHandle_0() const
{
	return m_Section_2_Object_FoundationModelHandle[0];
}

int MapTutorial::GetFoundationModelHandle_1() const
{
	return m_Section_2_Object_FoundationModelHandle[1];
}
int MapTutorial::GetFoundationModelHandle_2() const
{
	return m_Section_2_Object_FoundationModelHandle[2];
}