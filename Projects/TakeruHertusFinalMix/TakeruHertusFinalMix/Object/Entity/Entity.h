#pragma once
#include "../Component/Base/Component.h"
#include "../../Object/Component/Base/ComponentCommon.h"

/// <summary>
/// ���ׂẴI�u�W�F�N�g�𒇉��N���X�i�ʖ�Acter�j
/// </summary>
class Entity
{
private:
	std::unordered_map<std::string, std::shared_ptr<Component>> components;

protected:/*�ȉ��͌p����̃C���X�^���X�������ɃA�N�Z�X�ł��Ȃ��悤�Ƀv���e�N�g*/

	/// <summary>
	/// �R���|�[�l���g�𐶐�����
	/// </summary>
	template<typename T, typename... Args>
	void AddComponent(Args&&... args)
	{
		components[typeid(T).name()] = std::make_shared<T>(std::forward<Args>(args)...);
	}

	/// <summary>
	/// �R���|�[�l���g���擾����
	/// </summary>
	template<typename T>
	std::shared_ptr<T> GetComponent()
	{
		auto it = components.find(typeid(T).name());
		if (it != components.end())
		{
			return std::dynamic_pointer_cast<T>(it->second);
		}
		return nullptr;
	}

	/// <summary>
	/// <para>�s ���[�U�[��`�F�R���|�[�l���g�̏����� �t</para>
	/// <para>�I�u�W�F�N�g�̏������O��ɒǉ�����</para>
	/// </summary>
	void InitComponents();

	/// <summary>
	/// <para>�s ���[�U�[��`�F�R���|�[�l���g�̍X�V �t</para>
	/// <para>�I�u�W�F�N�g�̍X�V�O��ɒǉ�����</para>
	/// </summary>
	void UpdateComponents();

	/// <summary>
	/// <para>�s ���[�U�[��`�F�R���|�[�l���g�̕`�� �t</para>
	/// <para>�I�u�W�F�N�g�̕`��O��ɒǉ�����</para>
	/// </summary>
	void DrawComponents();

	/// <summary>
	/// <para>�s ���[�U�[��`�F�R���|�[�l���g�̉�� �t</para>
	/// <para>�I�u�W�F�N�g�̉���O��ɒǉ�����</para>
	/// </summary>
	void FinalComponents();
	
};

