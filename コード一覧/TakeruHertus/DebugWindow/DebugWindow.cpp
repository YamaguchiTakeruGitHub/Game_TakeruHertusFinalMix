#include "DebugWindow.h"

void DebugWindow::UpdateDebugInfo(int index, const std::string& info)
{
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
