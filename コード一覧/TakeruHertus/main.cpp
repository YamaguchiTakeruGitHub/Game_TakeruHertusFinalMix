#include "DxLib.h"
#include "Scene/SceneManager.h"
#include <thread>
#include <mutex>
#include <string>
#include <vector>
#include <EffekseerForDXLib.h>

// �f�o�b�O�p�̃e�L�X�g���X�g
std::vector<std::string> debugTexts = { "Initial Debug Info" };
std::mutex debugTextMutex;
// �f�o�b�O����ǉ�����֐�
void AddDebugInfo(const std::string& info) {
    std::lock_guard<std::mutex> lock(debugTextMutex);
    debugTexts.push_back(info);
    HWND hwnd = FindWindowA("DebugWindowClass", NULL);
    if (hwnd) {
        InvalidateRect(hwnd, NULL, TRUE); // �E�B���h�E���ĕ`��
    }
}
// �f�o�b�O�����X�V����֐�
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
        InvalidateRect(hwnd, NULL, TRUE); // �E�B���h�E���ĕ`��
    }
}
// �f�o�b�O�E�B���h�E�̃E�B���h�E�v���V�[�W��
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
// �f�o�b�O�E�B���h�E�̐����ƃ��b�Z�[�W���[�v�����s����֐�
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
// �f�o�b�O�E�B���h�E��ʃX���b�h�ŋN������֐�
void StartDebugWindow(HINSTANCE hInstance) {
    std::thread debugThread(DebugWindowThread, hInstance);
    debugThread.detach();
}





// WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // �Q�[���E�B���h�E�̏����ݒ�
    SetWindowText("TakeruHertus");
    SetGraphMode(1280, 740, 16);
    SetWindowSize(1280, 740);
    ChangeWindowMode(TRUE);


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
    SetChangeScreenModeGraphicsSystemResetFlag(false);
    Effekseer_SetGraphicsDeviceLostCallbackFunctions();



    SetDrawScreen(DX_SCREEN_BACK);
    // �V�[���}�l�[�W���[�̏�����
    SceneManager& sceneManager = SceneManager::GetInstance();
    sceneManager.Init();

    VECTOR position = VGet(0, 0, 0);
    VECTOR count = VGet(0, 0, 0);

    // �f�o�b�O�E�B���h�E�̋N��
    StartDebugWindow(hInstance);

    SetUseZBuffer3D(true);
    SetWriteZBuffer3D(true);
    

    SetUseBackCulling(true);
    //// �w�i�̐F���D�F�ɂ���
    //SetBackgroundColor(128, 128, 128);

    // �Q�[�����[�v
    while (ProcessMessage() != -1)
    {
        // �Q�[�������̊J�n�������L�^
        LONGLONG start = GetNowHiPerformanceCount();
        // �`���ʂ��N���A
        ClearDrawScreen();

        Effekseer_Sync3DSetting();

        // �V�[���̍X�V�ƕ`��
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
        // �f�o�b�O���̍X�V�i��Ƃ���FPS��\���j
        UpdateDebugInfo(0, "FPS: " + std::to_string(1000.0 / (GetNowHiPerformanceCount() - start + 1)));

        UpdateDebugInfo(1, "PlayerDebugData");
        UpdateDebugInfo(2, "Player Position: (" + std::to_string(position.x) + ", " + std::to_string(position.y) + ", " + std::to_string(position.z) + ")");
        UpdateDebugInfo(3, "Player Count: (" + std::to_string(count.x) + ", " + std::to_string(count.y) + ", " + std::to_string(count.z) + ")");

        sceneManager.DebugDraw();
       
#endif
        // ��ʂ̃t���b�v
        ScreenFlip();
        // ESC�L�[�ŃQ�[���I��
        if (CheckHitKey(KEY_INPUT_ESCAPE)) {
            break;
        }
        // FPS��60�ɌŒ�
        while (GetNowHiPerformanceCount() - start < 16667) {}
    }
    // �V�[���̏I��������DxLib�̏I��
    sceneManager.Final();
    Effkseer_End();
    DxLib_End();
    return 0;
}