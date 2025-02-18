#include "DxLib.h"
#include <EffekseerForDXLib.h>

#include "Scene/SceneManager.h"

#include <fstream>

// WinMain関数
int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow)
{
    // ゲームウィンドウの初期設定
    SetWindowText("TakeruHertusFinalMix");
    SetWindowIconID(333);


    //SetWindowSize(1280, 740);
    ChangeWindowMode(false);
    //ChangeWindowMode(true);

    SetGraphMode(1280, 740, 16);
    

    SetUseDirect3DVersion(DX_DIRECT3D_11);

    // DxLibの初期化
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

    /*セーブデータの初期設計元*/
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



    //// 背景の色を灰色にする
 //   SetBackgroundColor(128, 128, 128);

    SceneManager& sceneManager = SceneManager::GetInstance();
    sceneManager.Init();


    // ゲームループ
    while (ProcessMessage() != -1)
    {
        // ゲーム処理の開始時刻を記録
        LONGLONG start = GetNowHiPerformanceCount();
        // 描画画面をクリア
        ClearDrawScreen();
        //3Dエフェクトのセッティング
        Effekseer_Sync3DSetting();

        // ゲーム描画
  

        sceneManager.Update();
        sceneManager.Draw();

       

        // 画面のフリップ
        ScreenFlip();
        // ESCキーでゲーム終了
        if (CheckHitKey(KEY_INPUT_ESCAPE)) {
            break;
        }
        // FPSを60に固定
        while (GetNowHiPerformanceCount() - start < 16667) {}
    }

    sceneManager.Final();

    Effkseer_End();
    DxLib_End();
    return 0;
}