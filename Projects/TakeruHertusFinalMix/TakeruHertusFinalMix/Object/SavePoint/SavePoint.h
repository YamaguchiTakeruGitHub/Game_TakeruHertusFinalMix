#pragma once
#include "../Entity/Entity.h"
#include "../../UI/Easing/Easing.h"
#include "../../CSVLib/CsvData_Reading_And_Writing_Equipment.h"

class SavePoint : public Entity
{
private:
	std::shared_ptr<ComponentTransform> m_transform;

	
	std::shared_ptr<UIManager> m_UI;
	std::shared_ptr<InputDeviceManager> m_Idm;

	bool isSaving;
	bool isConfirming;
	int selectedSlot;
	int selectedConfirm;
	int saveleng;
	

	
	//外部ファイルの読み込み
	std::string saveFileNames[4];
	
	std::vector<std::vector<std::string>> Data;



public:
	SavePoint();

	void Init();
	void Update();
	void Draw();
	void Final();

	void SetPosition(const VECTOR& _pos) { m_transform->position = _pos; }
	VECTOR GetPosition() const { return m_transform->position; }

	void SetIsSaving(const bool& _isSaving) { isSaving = _isSaving; }
	bool GetIsSaving() const { return isSaving; }

};

