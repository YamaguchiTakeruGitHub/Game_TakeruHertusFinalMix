#pragma once
#include "JoyPad/JoyPad.h"
#include <memory>

class InputDeviceManager
{
public:
	InputDeviceManager();
	~InputDeviceManager();

	/// <summary>
	/// ���̓f�o�C�X�̏�����
	/// </summary>
	void Init();

	/// <summary>
	/// ���̓f�o�C�X�̍X�V
	/// �i���l�F�����ǉ����Ȃ��Ɠ��̓f�o�C�X�͔������܂���B�j
	/// </summary>
	void Update();
	
	//�W���C�p�b�h�̃C���X�^���X
	std::shared_ptr<JoyPad> joyPad;

};

