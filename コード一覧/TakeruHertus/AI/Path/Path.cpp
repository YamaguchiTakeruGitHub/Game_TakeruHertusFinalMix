#include "Path.h"

void Path::AddNode(const VECTOR& _position)
{
	nodes.push_back(PathNode{ _position });
}

void Path::DeleteNode()
{
	nodes.begin();
}


