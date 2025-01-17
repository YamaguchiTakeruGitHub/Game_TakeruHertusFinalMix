#include "EnemyMidle.h"

EnemyMidle::EnemyMidle()
	: Collidable(Collidable::Priority::High, GameObjectTag::EnemyMidle, ColliderData::Kind::Capsule)
	, modelHandle(MV1LoadModel("../Asset/3D/Character/Enemy/MidleEnemy/"))
{
	auto capsuleColliderData = std::dynamic_pointer_cast<ColliderDataCapsule3D>(m_colliderData);
	capsuleColliderData->size = 10.0f;
	capsuleColliderData->start = VAdd(m_righdbody.GetPosition(), VGet(0, capsuleColliderData->size, 0));
	capsuleColliderData->end = VSub(m_righdbody.GetPosition(), VGet(0, capsuleColliderData->size, 0));
	capsuleColliderData->radius = 10.0f;
}

EnemyMidle::~EnemyMidle()
{
}

void EnemyMidle::Init(std::shared_ptr<Physics> _physics)
{
	Collidable::Init(_physics);
	m_righdbody.Init(false);
	m_righdbody.SetPosition(VGet(0.0f, 20.0f, 80.0f));
	modelHandle = -1;
}

void EnemyMidle::Final(std::shared_ptr<Physics> _physics)
{
	Collidable::Final(_physics);
}

void EnemyMidle::Update(std::shared_ptr<Physics> _physics)
{
	auto capsuleData = std::dynamic_pointer_cast<ColliderDataCapsule3D>(m_colliderData);
	VECTOR start = m_righdbody.GetPosition();
	VECTOR END = VAdd(start, VGet(0, -capsuleData->radius, 0));



	// ���L�[�������Ă�����v���C���[���ړ�������
	// ���������肷��.
	VECTOR dir = VGet(0, 0, 0);
	dir.x = 0;
	dir.y = 0;
	if (CheckHitKey(KEY_INPUT_W) == 1)
	{
		dir.z = 3;
	}
	else if (CheckHitKey(KEY_INPUT_S) == 1)
	{
		dir.z = -3;
	}
	if (CheckHitKey(KEY_INPUT_A) == 1)
	{
		dir.x = -3;
	}
	else if (CheckHitKey(KEY_INPUT_D) == 1)
	{
		dir.x = 3;
	}

	// �]�v�Ȑ��l������̂ŁA�����ɒ����P�̌����Ƃ��Đ��K������
	if (VSquareSize(dir) > 0)
	{
		dir = VNorm(dir);
	}

	m_righdbody.SetVelocity(VGet(dir.x, dir.y, dir.z));
	MV1SetPosition(modelHandle, m_righdbody.GetPosition());
}

void EnemyMidle::Draw(std::shared_ptr<Physics> _physics)
{
	MV1DrawModel(modelHandle);
}

void EnemyMidle::OnCollide(const std::shared_ptr<Collidable>& _colider)
{
#ifdef _DEBUG
	std::string message = "���G��";
	if (_colider->GetTag() == GameObjectTag::EnemyMidle)
	{
		message += "���G";
	}
	else if (_colider->GetTag() == GameObjectTag::EnemyDinamic)
	{
		message += "��G";
	}
	else if (_colider->GetTag() == GameObjectTag::Enemy)
	{
		message += "�G";
	}
	else if (_colider->GetTag() == GameObjectTag::Player)
	{
		message += "�v���C���[";
	}

	message += "�Ɠ��������I\n";
	printfDx(message.c_str());
#endif // _DEBUG
}
