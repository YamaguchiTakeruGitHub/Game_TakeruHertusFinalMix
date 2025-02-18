#include "SavePoint.h"

SavePoint::SavePoint()
	: isSaving(false)
	, isConfirming(false)
	, selectedSlot(0)
	, selectedConfirm(0)
{
	AddComponent<ComponentTransform>();
	m_transform = GetComponent<ComponentTransform>();

	m_Idm = std::make_shared<InputDeviceManager>();
	m_UI = std::make_shared<UIManager>();
}

void SavePoint::Init()
{
    m_Idm->Init();

	Entity::InitComponents();
	isSaving = false;
	isConfirming = false;
	selectedSlot = 0;
	selectedConfirm = 0;

    saveleng = 0;

    m_transform->position = VGet(700, 4.0f, 700);

	saveFileNames[0] = "../SaveData/GameSaveData1.csv";
	saveFileNames[1] = "../SaveData/GameSaveData2.csv";
	saveFileNames[2] = "../SaveData/GameSaveData3.csv";
	saveFileNames[3] = "../SaveData/GameSaveData4.csv";

}

void SavePoint::Update()
{
    m_Idm->Update();

	Entity::UpdateComponents();
    if (isSaving) {
        // 上下キーでセーブスロット選択
        if (!isConfirming) {
            if (m_Idm->joyPad->isDUP == true) {
                selectedSlot = (selectedSlot - 1 + 4) % 4;
            }
            if (m_Idm->joyPad->isDDOWN == true) {
                selectedSlot = (selectedSlot + 1) % 4;
            }
            if (m_Idm->joyPad->isB == true) {
                isConfirming = true; // 確認画面に遷移
            }
            if (m_Idm->joyPad->isA == true) {
                isSaving = false; // メニューを閉じる
            }
        }
        else {

            if (saveleng >= 100)
            {
                saveleng = 100;
            }
            else
            {
                saveleng++;
            }

            // YES/NO 選択
            if (m_Idm->joyPad->isDLEFT == true || m_Idm->joyPad->isDRIGHT == true) {
                selectedConfirm = 1 - selectedConfirm; // 0と1を切り替え
            }
            if (m_Idm->joyPad->isB == true && saveleng >= 99) {
                if (selectedConfirm == 0) {

                    /*セーブ*/
                   /* Data1 = {
                      {"ID","Section"},
                      {"1","0"}
                     };*/

                    CSVLib::WriteCSV(saveFileNames[selectedSlot], Data);
                }
                isConfirming = false; // スロット選択画面に戻る
            }
        }
    }
}

void SavePoint::Draw()
{
	Entity::DrawComponents();
    if (isSaving) {
        // 背景描画（半透明）
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155);
        DrawBox(100, 100, 500, 400, GetColor(0, 0, 0), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        if (!isConfirming) {
            // スロット選択画面
            DrawString(150, 120, "セーブデータを選択", GetColor(255, 255, 255));
            for (int i = 0; i < 4; i++) {
                int color = (selectedSlot == i) ? GetColor(255, 255, 0) : GetColor(255, 255, 255);
                DrawString(170, 160 + i * 40, ("セーブデータ" + std::to_string(i + 1)).c_str(), color);
            }
        }
        else {
            // 確認画面
            DrawString(150, 200, "本当にセーブしますか?", GetColor(255, 255, 255));
            int yesColor = (selectedConfirm == 0) ? GetColor(255, 255, 0) : GetColor(255, 255, 255);
            int noColor = (selectedConfirm == 1) ? GetColor(255, 255, 0) : GetColor(255, 255, 255);
            DrawString(180, 250, "YES", yesColor);
            DrawString(280, 250, "NO", noColor);
        }
    }
}

void SavePoint::Final()
{
	Entity::FinalComponents();
}
