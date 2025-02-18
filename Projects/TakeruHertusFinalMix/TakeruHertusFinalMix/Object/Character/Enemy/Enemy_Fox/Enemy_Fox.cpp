#include "Enemy_Fox.h"


Enemy_Fox::Enemy_Fox()
	: m_isDad(false)
	, state(EnemyState::Idle)
	, m_hitPoint(0)
{
	AddComponent<ComponentTransform>();
	m_transform = GetComponent<ComponentTransform>();

	AddComponent<ComponentRightBody>();
	m_rightbody = GetComponent<ComponentRightBody>();

	AddComponent<ComponentModel>();
	m_model = GetComponent<ComponentModel>();

	AddComponent<ComponentAnimation>(m_model);
	m_animation = GetComponent<ComponentAnimation>();

	AddComponent<ComponentCollisionCapsule>(m_transform);
	m_capsule = GetComponent<ComponentCollisionCapsule>();

}

void Enemy_Fox::Init()
{
	Entity::InitComponents();
	filename = "../GameData/EnemyData.csv";
	Data = CSVLib::ReadCSV(filename);

	m_hitPoint = 100;

	m_transform->position = VGet(0, 0, 0);
	m_model->LoadModel("../Asset/3D/Enemy/Enemy_Fox/Enemy_fox.mv1");
	/*外部データ*/
	m_rightbody->speed = CSVLib::GetCell_float(Data, 1, 2);

	m_transform->scale = VGet(CSVLib::GetCell_float(Data, 1, 3),
		CSVLib::GetCell_float(Data, 1, 3),
		CSVLib::GetCell_float(Data, 1, 3));

	m_chaseDistance = CSVLib::GetCell_float(Data, 1, 4);
	m_attackDistance = CSVLib::GetCell_float(Data, 1, 5);
	m_attackDistance = 20.0f;

	/*カプセル*/
	m_capsule->radius = CSVLib::GetCell_float(Data, 1, 6);
	m_capsule->size = CSVLib::GetCell_float(Data, 1, 7);
	m_capsule->maxPosition = MV1GetFramePosition(m_model->modelHandle, 20);
	m_capsule->minPosition = MV1GetFramePosition(m_model->modelHandle, 8);

}
//
//void Enemy_Fox::Update(VECTOR& _playerPos)
//{
//	if (m_isDad) return;
//
//	UpdateAI(_playerPos);
//
//	Entity::UpdateComponents();
//	if (m_transform->position.y >= 50.0f)
//	{
//		m_transform->position.y--;
//	}
//	else
//	{
//		m_transform->position.y = 50.0f;
//	}
//	MV1SetPosition(m_model->modelHandle, m_transform->position);
//	MV1SetScale(m_model->modelHandle, m_transform->scale);
//	DrawFormatString(0, 0, 0xffffff, "pp.x:%f,pp.y:%f,pp.z:%f", _playerPos.x, _playerPos.y, _playerPos.z);
//
//}


void Enemy_Fox::Update(VECTOR _playerPos)
{
	//if (m_isDad) return;
#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "x:%f,y:%f,z:%f", _playerPos.x, _playerPos.y, _playerPos.z);
#endif // _DEBUG

	UpdateAI(_playerPos);

	Entity::UpdateComponents();
	if (m_transform->position.y >= 50.0f)
	{
		m_transform->position.y-=0.5f;
	}
	else
	{
		m_transform->position.y = 50.0f;
	}

	//アングルの更新
	m_transform->angle = std::atan2(-m_rightbody->direction.x, -m_rightbody->direction.z);

	//カプセルの最大最小値を取得
	m_capsule->maxPosition = MV1GetFramePosition(m_model->modelHandle, 8);
	m_capsule->minPosition = MV1GetFramePosition(m_model->modelHandle, 20);
	
	//ポジションのセット
	MV1SetPosition(m_model->modelHandle, m_transform->position);
	MV1SetRotationXYZ(m_model->modelHandle, VGet(0,m_transform->angle, 0));
	MV1SetScale(m_model->modelHandle, m_transform->scale);
}



void Enemy_Fox::Draw()
{
	//Entity::DrawComponents();
	
	if (m_tag == "section4")
	{
		m_model->Draw();
	}
#ifdef _DEBUG
	if (state == EnemyState::Idle)
	{
		DrawFormatString(100, 20, 0xffffff, "EnemyState:Idle");
	}
	if (state == EnemyState::Chase)
	{
		DrawFormatString(100, 20, 0xffffff, "EnemyState:Chase");
	}
	if (state == EnemyState::Attack)
	{
		DrawFormatString(100, 20, 0xffffff, "EnemyState:Attack");
	}
#endif // _DEBUG
}

void Enemy_Fox::Final()
{
	Entity::FinalComponents();
}

void Enemy_Fox::TakeDamage(int _damege)
{
	//if (m_isDad) return;
	m_hitPoint -= _damege;
	if (m_hitPoint <= 0)
	{
		state = EnemyState::Deth;
	}
}

void Enemy_Fox::UpdateAI(VECTOR _playerPos)
{
	float distance = VSize(VSub(_playerPos, m_transform->position));

	switch (state)
	{
	case EnemyState::Idle:
		m_animation->PlayAnim(3);
		if (distance <= m_chaseDistance)
		{
			state = EnemyState::Chase;
		}
		break;

	case EnemyState::Chase:
		m_animation->PlayAnim(8);
		MoveTowards(_playerPos);
		SetRandomTargetAround(_playerPos);
		if (distance <= m_attackDistance)
		{
			state = EnemyState::Attack;
		}
		if (distance >= m_chaseDistance)
		{
			state = EnemyState::Idle;
		}
		break;

	case EnemyState::Attack:
		AttackPlayer();
		m_animation->PlayAnim(6);
		if (distance >= m_attackDistance)
		{
			state = EnemyState::Chase;
		}
		break;

	case EnemyState::Deth:
		m_isDad = true;
		//死亡アニメーションやエフェクトを
		m_animation->PlayAnim(1);

		break;

	}

}

void Enemy_Fox::MoveTowards(VECTOR& _targetPos)
{
	VECTOR lengs = VSub(_targetPos, m_transform->position);

	float lengsSize = (lengs.x * lengs.x) + (lengs.y * lengs.y) + (lengs.z * lengs.z);

	m_rightbody->direction = VNorm(lengs); // 正規化して方向を取得
	m_transform->position = VAdd(m_transform->position, VScale(m_rightbody->direction, 1.0f)); // 移動
}


void Enemy_Fox::AttackPlayer()
{
}

void Enemy_Fox::SetRandomTargetAround(VECTOR& _playerPos)
{
	float angle = (float)(rand() % 360) * DX_PI_F / 180.0f;
	float radius = 50.0f + (rand() % 50);
	targetPosition.x = _playerPos.x + cosf(angle) * radius;
	targetPosition.y = _playerPos.y;
	targetPosition.z = _playerPos.z + sinf(angle) * radius;
}


