#include "DxLib.h"
#include "Scene/SceneManager.h"
#include <thread>
#include <mutex>
#include <string>
#include <vector>
#include <EffekseerForDXLib.h>

// デバッグ用のテキストリスト
std::vector<std::string> debugTexts = { "Initial Debug Info" };
std::mutex debugTextMutex;
// デバッグ情報を追加する関数
void AddDebugInfo(const std::string& info) {
    std::lock_guard<std::mutex> lock(debugTextMutex);
    debugTexts.push_back(info);
    HWND hwnd = FindWindowA("DebugWindowClass", NULL);
    if (hwnd) {
        InvalidateRect(hwnd, NULL, TRUE); // ウィンドウを再描画
    }
}
// デバッグ情報を更新する関数
void UpdateDebugInfo(int index, const std::string& info) {
    std::lock_guard<std::mutex> lock(debugTextMutex);
    if (index < debugTexts.size()) {
        debugTexts[index] = info;
    }
    else {
        debugTexts.push_back(info);
    }
    HWND hwnd = FindWindowA("DebugWindowClass", NULL);
    if (hwnd) {
        InvalidateRect(hwnd, NULL, TRUE); // ウィンドウを再描画
    }
}
// デバッグウィンドウのウィンドウプロシージャ
LRESULT CALLBACK DebugWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    switch (message) {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        {
            RECT rect;
            GetClientRect(hWnd, &rect);
            HBRUSH whiteBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
            FillRect(hdc, &rect, whiteBrush);
            std::lock_guard<std::mutex> lock(debugTextMutex);
            int y = 10;
            for (const auto& text : debugTexts) {
                TextOut(hdc, 10, y, text.c_str(), text.size());
                y += 20;
            }
        }
        EndPaint(hWnd, &ps);
        break;
    case WM_SIZE:
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
// デバッグウィンドウの生成とメッセージループを実行する関数
void DebugWindowThread(HINSTANCE hInstance) {
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = DebugWndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "DebugWindowClass";
    RegisterClass(&wc);
    HWND debugWnd = CreateWindowEx(
        0,
        "DebugWindowClass",
        "Debug Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 200,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(debugWnd, SW_SHOW);
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
// デバッグウィンドウを別スレッドで起動する関数
void StartDebugWindow(HINSTANCE hInstance) {
    std::thread debugThread(DebugWindowThread, hInstance);
    debugThread.detach();
}





// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // ゲームウィンドウの初期設定
    SetWindowText("TakeruHertus");
    SetGraphMode(1280, 740, 16);
    SetWindowSize(1280, 740);
    ChangeWindowMode(TRUE);


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
    SetChangeScreenModeGraphicsSystemResetFlag(false);
    Effekseer_SetGraphicsDeviceLostCallbackFunctions();



    SetDrawScreen(DX_SCREEN_BACK);
    // シーンマネージャーの初期化
    SceneManager& sceneManager = SceneManager::GetInstance();
    sceneManager.Init();

    VECTOR position = VGet(0, 0, 0);
    VECTOR count = VGet(0, 0, 0);

    // デバッグウィンドウの起動
    StartDebugWindow(hInstance);

    SetUseZBuffer3D(true);
    SetWriteZBuffer3D(true);
    

    SetUseBackCulling(true);
    //// 背景の色を灰色にする
    //SetBackgroundColor(128, 128, 128);

    // ゲームループ
    while (ProcessMessage() != -1)
    {
        // ゲーム処理の開始時刻を記録
        LONGLONG start = GetNowHiPerformanceCount();
        // 描画画面をクリア
        ClearDrawScreen();

        Effekseer_Sync3DSetting();

        // シーンの更新と描画
        sceneManager.Update();
        sceneManager.Draw();

        if (position.x >= 300.0f)
        {
            position.x = 0.0f;
        }
            
        position.x++;


        if (count.x >= 300.0f)
        {
            count.x = 0.0f;
        }

        count.x++;
        

#ifdef _DEBUG
        // デバッグ情報の更新（例としてFPSを表示）
        UpdateDebugInfo(0, "FPS: " + std::to_string(1000.0 / (GetNowHiPerformanceCount() - start + 1)));

        UpdateDebugInfo(1, "PlayerDebugData");
        UpdateDebugInfo(2, "Player Position: (" + std::to_string(position.x) + ", " + std::to_string(position.y) + ", " + std::to_string(position.z) + ")");
        UpdateDebugInfo(3, "Player Count: (" + std::to_string(count.x) + ", " + std::to_string(count.y) + ", " + std::to_string(count.z) + ")");

        sceneManager.DebugDraw();
       
#endif
        // 画面のフリップ
        ScreenFlip();
        // ESCキーでゲーム終了
        if (CheckHitKey(KEY_INPUT_ESCAPE)) {
            break;
        }
        // FPSを60に固定
        while (GetNowHiPerformanceCount() - start < 16667) {}
    }
    // シーンの終了処理とDxLibの終了
    sceneManager.Final();
    Effkseer_End();
    DxLib_End();
    return 0;
}