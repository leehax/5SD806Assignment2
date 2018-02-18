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

	std::map<std::pair<int,int>,AStarNode*> m_nodes;
	
	void FindPath(Tile* p_currentTile, Tile* p_targetTile); //Recursive path finding func
	Tile* NextTileInPath();

	void ClearOpenNodes();
	void ClearClosedNodes();
	void ClearCurrentPath();
	void Clear();
	void Draw();
private:

	bool m_initialized;
	void Initialize(Tile* p_currentTile, Tile* p_targetTile);
	AStarNode* NextNodeInPath();
	void RecursivePathFinding();
	AStarNode* m_startingNode;
	AStarNode* m_currentNode;
	AStarNode* m_goalNode;

	std::vector < AStarNode*> m_openNodes; //todo: implement linked list maybe
	std::vector < AStarNode*> m_closedNodes;
	std::vector < AStarNode*> AdjacentNodes(AStarNode* p_cur);
	std::vector< Tile* > m_tilesInPath;
	std::vector < AStarNode*> m_nodesInPath;
	DrawManager* m_drawManager;
	int m_recurseAmount;
};

