#include "stdafx.h"
#include "PathFindNode.h"
#include "Tile.h"

PathFindNode::PathFindNode(Tile* p_tile)
{
	m_tile = p_tile;
}


PathFindNode::~PathFindNode()
{
}

int PathFindNode::GetFCost()
{
	return m_gCost + m_hCost + TypeModifier();
}

int PathFindNode::TypeModifier()
{
	return m_tile->m_type * 20;
}

Vector2<int> PathFindNode::GetGridPos()
{
	return m_tile->GetGridPos();
}

bool PathFindNode::m_blocked()
{
	return m_tile->IsBlocked();
}
