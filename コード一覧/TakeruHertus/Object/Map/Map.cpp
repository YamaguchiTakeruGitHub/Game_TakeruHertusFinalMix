#include "Map.h"

void Map::DrawGridLines()
{
	for (int x = 0; x <= GRID::X; x++)
	{
		for (int z = 0; z <= GRID::Z; z++)
		{
			VECTOR start = VGet(x * GRID::CELL_SIZE, 0.0f, z * GRID::CELL_SIZE);
			VECTOR end = VGet(x * GRID::CELL_SIZE, GRID::Y, z * GRID::CELL_SIZE);
			DrawLine3D(start, end, 0x646464);
			start = VGet(0.0f, x * GRID::CELL_SIZE, z * GRID::CELL_SIZE);
			end = VGet(GRID::X * GRID::CELL_SIZE, x * GRID::CELL_SIZE, z * GRID::CELL_SIZE);
			DrawLine3D(start, end, 0x646464);

		}
	}
}

void Map::HighlightPlayerCell(const VECTOR& _playerPos)
{
	VECTOR gridPos = WorldToGrid(_playerPos);
	VECTOR cellMin = VGet(gridPos.x * GRID::CELL_SIZE, gridPos.y * GRID::CELL_SIZE, gridPos.z * GRID::CELL_SIZE);
	VECTOR cellMax = VGet((gridPos.x + 1) * GRID::CELL_SIZE, (gridPos.y + 1) * GRID::CELL_SIZE, (gridPos.z + 1) * GRID::CELL_SIZE);
	DrawBox3DLine(cellMin, cellMax, 0xff0000);
}

void Map::RegisterObjectToGrid(int _objectID, VECTOR _pos)
{
	VECTOR gridPos = WorldToGrid(_pos);
	int gx = static_cast<int>(gridPos.x);
	int gy = static_cast<int>(gridPos.y);
	int gz = static_cast<int>(gridPos.z);

	if (gx >= 0 && gx < GRID::X && gy >= 0 && gy < GRID::Y && gz >= 0 && gz < GRID::Z)
	{
		grid[gx][gy][gz].objectIDs.push_back(_objectID);
	}
}

std::vector<VECTOR> Map::GetAbjacentCells(VECTOR _pos, int _range)
{
	VECTOR gridPos = WorldToGrid(_pos);
	std::vector<VECTOR> adjacentCells;
	for (int dx = -_range; dx <= _range; dx++)
	{
		for (int dy = -_range; dy <= _range; dy++)
		{
			for (int dz = -_range; dz <= _range; dz++)
			{
				VECTOR cell = VGet(gridPos.x + dx, gridPos.y + dy, gridPos.z + dz);
				if (cell.x >= 0 && cell.x < GRID::X && cell.y >= 0 && cell.y < GRID::Y && cell.z >= 0 && cell.z <= GRID::Z)
				{
					adjacentCells.push_back(cell);
				}
			}
		}
	}

	return adjacentCells;
}

void Map::CheckAndResolveCollisions(VECTOR& _playerPos, int _range)
{
	auto adjacentCells = GetAbjacentCells(_playerPos, _range);
	for (const auto& cell : adjacentCells)
	{
		int gx = static_cast<int>(cell.x);
		int gy = static_cast<int>(cell.y);
		int gz = static_cast<int>(cell.z);

		for (int objectID : grid[gx][gy][gz].objectIDs)
		{
			VECTOR capsuleStart = _playerPos;
			VECTOR capsuleEnd = VAdd(_playerPos, VGet(0, 1, 0));
			float capsuleRadius = 0.5f;
			auto collision = MV1CollCheck_Capsule(mapModel,1, capsuleStart, capsuleEnd, capsuleRadius);

			//if(collision == 1)

		}

	}
}

void Map::DrawBox3DLine(VECTOR minPos, VECTOR maxPos, unsigned int color)
{
	// 底面の4点
	VECTOR p1 = VGet(minPos.x, minPos.y, minPos.z);
	VECTOR p2 = VGet(maxPos.x, minPos.y, minPos.z);
	VECTOR p3 = VGet(maxPos.x, minPos.y, maxPos.z);
	VECTOR p4 = VGet(minPos.x, minPos.y, maxPos.z);

	// 上面の4点
	VECTOR p5 = VGet(minPos.x, maxPos.y, minPos.z);
	VECTOR p6 = VGet(maxPos.x, maxPos.y, minPos.z);
	VECTOR p7 = VGet(maxPos.x, maxPos.y, maxPos.z);
	VECTOR p8 = VGet(minPos.x, maxPos.y, maxPos.z);

	// 下側の四角形
	DrawLine3D(p1, p2, color);
	DrawLine3D(p2, p3, color);
	DrawLine3D(p3, p4, color);
	DrawLine3D(p4, p1, color);

	// 上側の四角形
	DrawLine3D(p5, p6, color);
	DrawLine3D(p6, p7, color);
	DrawLine3D(p7, p8, color);
	DrawLine3D(p8, p5, color);

	// 縦のライン
	DrawLine3D(p1, p5, color);
	DrawLine3D(p2, p6, color);
	DrawLine3D(p3, p7, color);
	DrawLine3D(p4, p8, color);
}

