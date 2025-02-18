#pragma once
#include <iostream>
#include <memory>
#include <mutex>

/// <summary>
/// �V���O���g���e���v���[�g�N���X
/// </summary>
/// <typeparam name="T">�V���O���g�����������N���X</typeparam>
template<typename T>
class Singleton
{
public:
	//�C���X�^���X���擾����ÓI���\�b�h
	static std::shared_ptr<T> Instance()
	{
		//����Ăяo�����ɃC���X�^���X�𐶐�
		std::call_once(initFlag, []() {instance = std::shared_ptr<T>(new T()); });
		return instance;
	}

protected:
	/*protected�ɂ��ĊO������̐�����h��*/
	Singleton() {}
	~Singleton() {}

private:
	static std::shared_ptr<T> instance;//�B��̃C���X�^���X
	static std::once_flag initFlag;	   //�������t���O
	
	//�R�s�[�R���X�g���N�^�Ƒ�����Z�q���폜���ĕ�����h��
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

};
//�ÓI�����o�ϐ��̏�����
template<typename T>
std::shared_ptr<T> Singleton<T>::instance = nullptr;

template<typename T>
std::once_flag Singleton<T>::initFlag;

/*MEMO*/
//�V���O���g���Ƃ̓C���X�^���X���P�����쐬���Ă�����g���܂킷���ƁB
// ����ɂ�蕡���̃C���X�^���X���֎~���邱�Ƃ��ł��邽�߁B
// �����f�[�^�ɑ΂���ύX�̋�����h�����Ƃ��ł���B
// ��F�ݒ����T�E���h�}�l�[�W���[�A�A�j���[�V�����Ȃ�
// �܂����S���������O���[�o���ȃA�N�Z�X��񋟂��邱�Ƃ��ł���B