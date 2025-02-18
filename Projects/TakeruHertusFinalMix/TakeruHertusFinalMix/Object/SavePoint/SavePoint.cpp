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
        // �㉺�L�[�ŃZ�[�u�X���b�g�I��
        if (!isConfirming) {
            if (m_Idm->joyPad->isDUP == true) {
                selectedSlot = (selectedSlot - 1 + 4) % 4;
            }
            if (m_Idm->joyPad->isDDOWN == true) {
                selectedSlot = (selectedSlot + 1) % 4;
            }
            if (m_Idm->joyPad->isB == true) {
                isConfirming = true; // �m�F��ʂɑJ��
            }
            if (m_Idm->joyPad->isA == true) {
                isSaving = false; // ���j���[�����
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

            // YES/NO �I��
            if (m_Idm->joyPad->isDLEFT == true || m_Idm->joyPad->isDRIGHT == true) {
                selectedConfirm = 1 - selectedConfirm; // 0��1��؂�ւ�
            }
            if (m_Idm->joyPad->isB == true && saveleng >= 99) {
                if (selectedConfirm == 0) {

                    /*�Z�[�u*/
                   /* Data1 = {
                      {"ID","Section"},
                      {"1","0"}
                     };*/

                    CSVLib::WriteCSV(saveFileNames[selectedSlot], Data);
                }
                isConfirming = false; // �X���b�g�I����ʂɖ߂�
            }
        }
    }
}

void SavePoint::Draw()
{
	Entity::DrawComponents();
    if (isSaving) {
        // �w�i�`��i�������j
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155);
        DrawBox(100, 100, 500, 400, GetColor(0, 0, 0), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        if (!isConfirming) {
            // �X���b�g�I�����
            DrawString(150, 120, "�Z�[�u�f�[�^��I��", GetColor(255, 255, 255));
            for (int i = 0; i < 4; i++) {
                int color = (selectedSlot == i) ? GetColor(255, 255, 0) : GetColor(255, 255, 255);
                DrawString(170, 160 + i * 40, ("�Z�[�u�f�[�^" + std::to_string(i + 1)).c_str(), color);
            }
        }
        else {
            // �m�F���
            DrawString(150, 200, "�{���ɃZ�[�u���܂���?", GetColor(255, 255, 255));
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
