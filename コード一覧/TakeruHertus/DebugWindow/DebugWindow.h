#pragma once
#include <DxLib.h>
#include <thread>
#include <mutex>
#include <string>
#include <vector>

class DebugWindow
{
public:
	
	void UpdateDebugInfo(int index, const std::string& info);

private:
	// デバッグ用のテキストリスト
	std::vector<std::string> debugTexts = { "Initial Debug Info" };
	std::mutex debugTextMutex;
};

