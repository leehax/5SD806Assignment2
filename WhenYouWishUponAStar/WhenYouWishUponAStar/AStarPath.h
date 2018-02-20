#pragma once
#include <vector>
#include <memory>
#include "Math.h"
#include "Config.h"
#include <map>
class Tile;
class AStarNode;
class World;
class DrawManager;
class AStarPath
{
public:
	AStarPath(World* p_world);
	~AStarPath();
	
	std::vector< Tile* > FindPath(Tile* p_currentTile, Tile* p_targetTile); //Test with returning a vector of nodes, and having the agent construct the vector of tiles from that data
	void Recalculate();
	void Draw();

private:

	bool m_initialized;
	void Initialize(Tile* p_currentTile, Tile* p_targetTile);

	std::vector< Tile* > RecursivePathFinding();
	std::vector< Tile* > m_tilesInPath;

	AStarNode* m_startingNode;
	AStarNode* m_currentNode;
	AStarNode* m_goalNode;

	std::map<std::pair<int, int>, AStarNode*> m_nodes;
	std::vector < AStarNode*> m_openNodes; 
	std::vector < AStarNode*> m_closedNodes;
	std::vector < AStarNode*> m_nodesInPath;
	std::vector < AStarNode*> AdjacentNodes(AStarNode* p_cur);
	
	DrawManager* m_drawManager;

};

