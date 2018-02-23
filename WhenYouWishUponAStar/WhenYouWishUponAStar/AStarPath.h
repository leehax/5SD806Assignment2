#pragma once
#include <vector>
#include <map>
class Tile;
class PathFindNode;
class World;
class DrawManager;
class AStarPath
{
public:
	AStarPath(World* p_world);
	~AStarPath();
	
	std::vector< Tile* > FindPath(Tile* p_currentTile, Tile* p_targetTile); //this could be refactored to return a vector of nodes, in which case the pahtfining agent would use the nodes to build the vector of tiles
	void Recalculate();
	void Draw();

private:

	bool m_initialized;
	void Initialize(Tile* p_currentTile, Tile* p_targetTile);

	std::vector< Tile* > RecursivePathFinding(); 
	std::vector< Tile* > m_tilesInPath;

	PathFindNode* m_startingNode;
	PathFindNode* m_currentNode;
	PathFindNode* m_goalNode;

	std::map<std::pair<int, int>, PathFindNode*> m_nodes;
	std::vector < PathFindNode*> m_openNodes; 
	std::vector < PathFindNode*> m_closedNodes;
	std::vector < PathFindNode*> m_nodesInPath;
	std::vector < PathFindNode*> AdjacentNodes(PathFindNode* p_cur);
	
	DrawManager* m_drawManager;

};

