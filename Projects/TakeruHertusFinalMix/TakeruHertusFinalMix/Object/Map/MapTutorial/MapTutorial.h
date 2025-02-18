#pragma once
#include "../Base/Map.h"

class MapTutorial : public Map
{
private:
	std::shared_ptr<ComponentTransform> m_transform;
	std::shared_ptr<ComponentModel> m_model;
	std::shared_ptr<ComponentCollisionPolygon> m_polygon;

	/*セクション２で表示するオブジェクト*/
	int m_Section_2_Object_FoundationModelHandle[3];
	VECTOR m_Section_2_Object_FoundationPosition[3];

	bool m_isSection_2;
	int m_section_2_Time;
	int m_section_2_MaxTime;

	bool m_isSection_4;

	const char* m_tag;

public:
	MapTutorial();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

	int GetFoundationModelHandle_0()const;
	int GetFoundationModelHandle_1()const;
	int GetFoundationModelHandle_2()const;



	int GetModelHandle() { return m_model->modelHandle; }
	VECTOR GetPosition() { return m_transform->position; }

	MV1_REF_POLYGONLIST GetPolygonList() { return m_polygon->polygonList; }
	void SetPolygonList(const MV1_REF_POLYGONLIST& _polygonList) { m_polygon->polygonList = _polygonList; }

	void SetIsSection_2(const bool& _isSection2) { m_isSection_2 = _isSection2; }
	bool GetIsSection_2() const { return m_isSection_2; }

	void SetIsSection_4(const bool& _isSection4) { m_isSection_4 = _isSection4; }
	bool GetISSection_4() const { return m_isSection_4; }

	void SetTag(const char* _tag) { m_tag = _tag; }
	const char* GetTag() const { return m_tag; }

};

