#include "stdafx.h"
#include "AStarNode.h"
#include "Tile.h"

AStarNode::AStarNode(Tile* p_tile)
{
	m_tile = p_tile;
}


AStarNode::~AStarNode()
{
}

int AStarNode::GetFCost()
{
	return m_gCost + m_hCost + TypeModifier();
}

int AStarNode::TypeModifier()
{
	return m_tile->m_type * 20;
}

bool AStarNode::m_blocked()
{
	return m_tile->IsBlocked();
}
