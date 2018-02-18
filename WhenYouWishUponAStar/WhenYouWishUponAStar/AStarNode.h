#pragma once
#include <memory>
class Tile;
class AStarNode
{
public:
	AStarNode(Tile* p_tile);
	~AStarNode();

	int GetFCost();
	int m_gCost = 0; //travel/accumulated cost
	int m_hCost = 0; //heuristic cost
	int TypeModifier();

	Tile* m_tile = nullptr;
	AStarNode* m_parentNode= nullptr;

	bool m_blocked(); //get m_tile blocked
};

