#include "EnemyDinamic.h"
#include <string>

EnemyDinamic::EnemyDinamic()
	: Collidable(Collidable::Priority::Static, GameObjectTag::EnemyMidle, ColliderData::Kind::Capsule)
	, modelHandle(-1)
{
	auto capsuleColliderData = std::dynamic_pointer_cast<ColliderDataCapsule3D>(m_colliderData);
	capsuleColliderData->size = 10.0f;
	capsuleColliderData->start = VAdd(m_righdbody.GetPosition(), VGet(0, capsuleColliderData->size, 0));
	capsuleColliderData->end = VSub(m_righdbody.GetPosition(), VGet(0, capsuleColliderData->size, 0));
	capsuleColliderData->radius = 10.0f;
}

EnemyDinamic::~EnemyDinamic()
{
}

void EnemyDinamic::Init(std::shared_ptr<Physics> _physics)
{
	Collidable::Init(_physics);
	m_righdbody.Init(false);
	m_righdbody.SetPosition(VGet(0.0f, 20.0f, 30.0f));
	modelHandle = -1;
}

void EnemyDinamic::Final(std::shared_ptr<Physics> _physics)
{
	Collidable::Final(_physics);
}

void EnemyDinamic::Update(std::shared_ptr<Physics> _physics)
{
	auto capsuleData = std::dynamic_pointer_cast<ColliderDataCapsule3D>(m_colliderData);
	VECTOR start = m_righdbody.GetPosition();
	VECTOR END = VAdd(start, VGet(0, -capsuleData->radius, 0));



	// 矢印キーを押していたらプレイヤーを移動させる
	// 向きを決定する.
	VECTOR dir = VGet(0, 0, 0);
	dir.x = 0;
	dir.y = 0;
	if (CheckHitKey(KEY_INPUT_UP) == 1)
	{
		dir.z = 3;
	}
	else if (CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		dir.z = -3;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		dir.x = -3;
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		dir.x = 3;
	}

	// 余計な数値が入るので、純粋に長さ１の向きとして正規化する
	if (VSquareSize(dir) > 0)
	{
		dir = VNorm(dir);
	}

	m_righdbody.SetVelocity(VGet(dir.x, dir.y, dir.z));
	MV1SetPosition(modelHandle, m_righdbody.GetPosition());
}

void EnemyDinamic::Draw(std::shared_ptr<Physics> _physics)
{
}

void EnemyDinamic::OnCollide(const std::shared_ptr<Collidable>& _colider)
{
#ifdef _DEBUG
	std::string message = "大敵が";
	if (_colider->GetTag() == GameObjectTag::EnemyDinamic)
	{
		message += "大敵";
	}
	else if (_colider->GetTag() == GameObjectTag::EnemyMidle)
	{
		message += "中敵";
	}
	else if (_colider->GetTag() == GameObjectTag::Enemy)
	{
		message += "敵";
	}
	else if (_colider->GetTag() == GameObjectTag::Player)
	{
		message += "プレイヤー";
	}

	message += "と当たった！\n";
	printfDx(message.c_str());
#endif // _DEBUG
}
