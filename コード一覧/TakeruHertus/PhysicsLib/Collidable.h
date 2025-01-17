#pragma once
#include "GameObjectTag.h"//�Q�[���I�u�W�F�N�g�̃^�O
#include "PhysicsLib.h"//�������C�u����


class Rigidbody;
class Physics;
class ColliderData;

/// <summary>
/// �Փ˂��ł�����́A������Փ˔�����s���ꍇ�͂�����p��������
/// </summary>
class Collidable abstract//�����I�ɒ��ۃN���X�ɂ���
{
public:

	//�ʒu�␳�̗D�揇�ʂ̔���
	enum class Priority : int
	{
		Low,		//��
		High,		//��
		Static,		//�����Ȃ�
	};

	Collidable(Priority _prioriy, GameObjectTag _tag, ColliderData::Kind _colliderKind);
	virtual ~Collidable();
	virtual void Init(std::shared_ptr<Physics> _physics);
	virtual void Final(std::shared_ptr<Physics> _physics);

	///// <summary>
	///// �Փ˂�����
	///// </summary>
	///// <param name="_collider"></param>
	//virtual void OnCollide(const Collidable& _collider) abstract;//�����I�ɒ��ۉ�����

	/// <summary>
	/// �Փ˂�����
	/// </summary>
	/// <param name="_collider"></param>
	virtual void OnCollide(const std::shared_ptr<Collidable>& _collider) abstract;//�����I�ɒ��ۉ�����



	/// <summary>
	/// �^�O���
	/// </summary>
	/// <returns></returns>
	GameObjectTag GetTag() const { return m_tag; }

	/// <summary>
	/// �D��x
	/// </summary>
	/// <returns></returns>
	Priority GetPriority() const { return m_priority; }


protected:
	Rigidbody m_righdbody;						//�����f�[�^
	std::shared_ptr<ColliderData> m_colliderData;	//�����蔻��f�[�^

private:

	/// <summary>
	/// �����蔻��̎�ނ𐶐�����
	/// </summary>
	/// <param name="_kind"></param>
	/// <returns></returns>
	std::shared_ptr<ColliderData> CreateColliderData(ColliderData::Kind _kind);

	GameObjectTag m_tag;
	
	Priority m_priority;

	//Physics�N���X��Collidable�����R�ɊǗ����邽�߂Ƀt�����h���i�ǂ�ȋ��ł��A�N�Z�X�ł���j
	friend Physics;

private:
	VECTOR m_nextPos;

};

