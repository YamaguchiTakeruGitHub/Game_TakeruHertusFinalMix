#pragma once
#include <DxLib.h>
#include <vector>
#include <cmath>

namespace GRID
{
	const int X = 10;
	const int Y = 10;
	const int Z = 10;

	const float CELL_SIZE = 10.0f;
};

class Map
{
public:
	

	VECTOR WorldToGrid(VECTOR _pos) { return VGet(floor(_pos.x / GRID::CELL_SIZE), floor(_pos.y / GRID::CELL_SIZE), floor(_pos.z / GRID::CELL_SIZE)); }
	void DrawGridLines();
	void HighlightPlayerCell(const VECTOR& _playerPos);
	void RegisterObjectToGrid(int objectID, VECTOR _pos);
	std::vector<VECTOR> GetAbjacentCells(VECTOR _pos, int _range);
	void CheckAndResolveCollisions(VECTOR& _playerPos, int _range);

private:
	int mapModel;

	struct GridCell { std::vector<float> objectIDs; };
	GridCell grid[GRID::X][GRID::Y][GRID::Z];
	
	void DrawBox3DLine(VECTOR minPos, VECTOR maxPos, unsigned int color);

};

