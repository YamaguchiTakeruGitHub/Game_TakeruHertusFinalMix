#pragma once
#include "JoyPad/JoyPad.h"

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


	//�C���X�^���X�n
	JoyPad* joyPad;

};
