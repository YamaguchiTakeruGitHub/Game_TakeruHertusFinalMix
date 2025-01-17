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
	// �f�o�b�O�p�̃e�L�X�g���X�g
	std::vector<std::string> debugTexts = { "Initial Debug Info" };
	std::mutex debugTextMutex;
};

