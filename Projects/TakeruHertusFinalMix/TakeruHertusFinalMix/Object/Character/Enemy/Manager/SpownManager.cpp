#include "SpownManager.h"


void SpownManager::AddSpawnPoint(VECTOR _position)
{
	m_spawnPoints.push_back({ _position, false });
}

void SpownManager::SpawnEnemy(int _spawnIndex)
{
	if (!m_spawnPoints[_spawnIndex].isOccupied)
	{
		m_spawnPoints[_spawnIndex].isOccupied = true;
		//m_enemyFoxs.push_back(std::make_shared<Enemy_Fox>(m_spawnPoints[_spawnIndex].position, "../Asset/3D/Enemy/Enemy_Fox/Enemy_fox.mv1"));
	}
}

void SpownManager::HandleEnemyDeath(std::shared_ptr<Enemy_Fox> _enemyFox)
{
	_enemyFox->SetIsDad(true);
	// 死んだ敵をリストから削除する処理
	auto it = std::find(m_enemyFoxs.begin(), m_enemyFoxs.end(), _enemyFox);
	if (it != m_enemyFoxs.end()) {
		m_enemyFoxs.erase(it); // 死んだ敵をリストから削除
	}
}


void SpownManager::OnStageTransition()
{
	for (auto& spawn : m_spawnPoints)
	{
		spawn.isOccupied = false;
	}

	for (size_t i = 0; i < m_spawnPoints.size(); i++)
	{
		if (!m_spawnPoints[i].isOccupied)
		{
			SpawnEnemy(i);
		}
	}
}

void SpownManager::ResetEnemies()
{
	m_enemyFoxs.clear();
	for (auto& spawnPoint : m_spawnPoints)
	{
		spawnPoint.isOccupied = false;
	}
}

bool SpownManager::IsPlayerInSpawnZone(VECTOR _playerPos, int _spawnIndex)
{
	return m_collision->CheckSphereHitCollision(_playerPos, 50.0f, m_spawnPoints[_spawnIndex].position, 50.0f);
}



void SpownManager::Init()
{
	for (auto& enemy : m_enemyFoxs)
	{
		enemy->Init();
	}
}

void SpownManager::Update(VECTOR _playerPos)
{
	for (auto& enemy : m_enemyFoxs)
	{
		if (!enemy->GetIsDad())
		{
			enemy->Update(_playerPos);
		}
	}
}

void SpownManager::Draw()
{
	for (auto& enemy : m_enemyFoxs)
	{
		if (!enemy->GetIsDad())
		{
			enemy->Draw();
		}
	}
}

void SpownManager::Final()
{
	for (auto& enemy : m_enemyFoxs)
	{
		enemy->Final();
	}
}
