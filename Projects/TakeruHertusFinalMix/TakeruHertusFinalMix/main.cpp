#include "DxLib.h"
#include <EffekseerForDXLib.h>

#include "Scene/SceneManager.h"

#include <fstream>

// WinMain�֐�
int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow)
{
    // �Q�[���E�B���h�E�̏����ݒ�
    SetWindowText("TakeruHertusFinalMix");
    SetWindowIconID(333);


    //SetWindowSize(1280, 740);
    ChangeWindowMode(false);
    //ChangeWindowMode(true);

    SetGraphMode(1280, 740, 16);
    

    SetUseDirect3DVersion(DX_DIRECT3D_11);

    // DxLib�̏�����
    if (DxLib_Init() == -1) {
        return -1;
    }

    if (Effekseer_Init(8000) == -1)
    {
        DxLib_End();
        return -1;
    }

    SetDrawScreen(DX_SCREEN_BACK);
    SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
    Effekseer_SetGraphicsDeviceLostCallbackFunctions();

    

    SetUseZBuffer3D(true);
    SetWriteZBuffer3D(true);
    SetUseBackCulling(true);

    /*�Z�[�u�f�[�^�̏����݌v��*/
    /*testproguram_start*/
    std::ofstream file("../SaveData/SaveData1.dat");
    if (file.is_open())
    {
        file << "waithtest1\n";
        file << "waithtest2";
        file.close();
    }

    std::ofstream file2("../SaveData/SaveData2.dat");
    if (file2.is_open())
    {
        file2 << "waithtest1\n";
        file2 << "waithtest2";
        file2.close();
    }
    /*testproguram_end*/



    //// �w�i�̐F���D�F�ɂ���
 //   SetBackgroundColor(128, 128, 128);

    SceneManager& sceneManager = SceneManager::GetInstance();
    sceneManager.Init();


    // �Q�[�����[�v
    while (ProcessMessage() != -1)
    {
        // �Q�[�������̊J�n�������L�^
        LONGLONG start = GetNowHiPerformanceCount();
        // �`���ʂ��N���A
        ClearDrawScreen();
        //3D�G�t�F�N�g�̃Z�b�e�B���O
        Effekseer_Sync3DSetting();

        // �Q�[���`��
  

        sceneManager.Update();
        sceneManager.Draw();

       

        // ��ʂ̃t���b�v
        ScreenFlip();
        // ESC�L�[�ŃQ�[���I��
        if (CheckHitKey(KEY_INPUT_ESCAPE)) {
            break;
        }
        // FPS��60�ɌŒ�
        while (GetNowHiPerformanceCount() - start < 16667) {}
    }

    sceneManager.Final();

    Effkseer_End();
    DxLib_End();
    return 0;
}