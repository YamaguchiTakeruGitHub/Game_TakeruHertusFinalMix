#pragma once
#include "../Enemy_Fox/Enemy_Fox.h"
#include "../../../Collision/Collision.h"

struct SpawnPoint
{
	VECTOR position;
	bool isOccupied;
};

class SpownManager
{
private:
	std::vector<SpawnPoint> m_spawnPoints;
	std::vector<std::shared_ptr<Enemy_Fox>> m_enemyFoxs;
	std::shared_ptr<Collision> m_collision = std::make_shared<Collision>();
public:

	void AddSpawnPoint(VECTOR _position);
	void SpawnEnemy(int _spawnIndex);
	void HandleEnemyDeath(std::shared_ptr<Enemy_Fox> _enemyFox);
	void OnStageTransition();
	void ResetEnemies();
	bool IsPlayerInSpawnZone(VECTOR _playerPos, int spawnIndex);
	int GetSpawnPointCount() const { return m_spawnPoints.size(); }
	
	void Init();
	void Update(VECTOR _playerPos);
	void Draw();
	void Final();

};

