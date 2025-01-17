#pragma once
#include <list>
#include <vector>
#include <cassert>

#include "PhysicsLib.h"
#include "../MathLib/MathLib.h"

class Collidable;

class Physics final
{
public:

	/// <summary>
	/// �Փ˕��̓o�^
	/// </summary>
	/// <param name="_collidable"></param>
	void Entry(std::shared_ptr<Collidable> _collidable);

	/// <summary>
	/// �Փ˕��̓o�^����
	/// </summary>
	/// <param name="_collidable"></param>
	void Exit(std::shared_ptr<Collidable> _collidable);

	/// <summary>
	/// �X�V�i�o�^�I�u�W�F�N�g�̕����ړ��A�Փ˒ʒm�j
	/// </summary>
	void Update();

	std::list<std::shared_ptr<Collidable>> IsCollideLine(const VECTOR& _start, const VECTOR& _end) const;

	static constexpr float m_gravity = -0.01f;
	static constexpr float m_maxGravityAccel = -0.15f;

private:
	static const int BeforFixInfoColor = 0x0000ff;//�␳�O���F
	static const int AimInfoColor	   = 0x0000aa;//�␳�O�\����F
	static const int AfterFixInfoColor = 0xff00ff;//�␳����F

	//�o�^���ꂽCollidable�̃��X�g
	std::list<std::shared_ptr<Collidable>> m_collidables;

	//�x���ʒm�̂��߂̃f�[�^
	struct OnCollideInfo
	{
		std::shared_ptr<Collidable> owner = std::make_shared<Collidable>();
		std::shared_ptr<Collidable> colider = std::make_shared<Collidable>();
		void OnCollide();
	};


	//�����蔻��̃`�F�b�N
	std::vector<OnCollideInfo> CheckColide() const;

	//�Փ˂��Ă��邩�ۂ�
	bool IsCollide(const std::shared_ptr<Collidable> _objA, const std::shared_ptr<Collidable> _objB) const;

	//�ʒu�̕␳
	void FixNextPosition(std::shared_ptr<Collidable> _primary, std::shared_ptr<Collidable> _secondary) const;

	//�ʒu�̊m��
	void FixPosition();
	
};

