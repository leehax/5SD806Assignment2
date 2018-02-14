#pragma once
#include <memory>
class Tile;
class AStarNode
{
public:
	AStarNode();
	~AStarNode();

	int m_fCost = 0; //f=g+h
	int m_gCost = 0; //travel/accumulated cost
	int m_hCost = 0; //heuristic cost
	int m_typeModifier = 0;

	std::shared_ptr < Tile > m_tile = nullptr;
	std::shared_ptr < AStarNode > m_parentNode= nullptr;

	bool m_blocked; //get m_tile blocked
};

