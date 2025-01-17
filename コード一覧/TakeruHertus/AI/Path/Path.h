#pragma once
#include <vector>
#include <DxLib.h>

struct PathNode
{
	VECTOR position;
};

class Path
{
public:
	std::vector<PathNode> nodes;

	void AddNode(const VECTOR& _position);

	void DeleteNode();

};

