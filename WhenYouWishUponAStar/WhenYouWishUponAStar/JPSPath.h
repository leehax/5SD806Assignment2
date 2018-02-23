#pragma once
#include <vector>
#include <map>
#include "Math.h"
class Tile;
class PathFindNode;
class World;
class DrawManager;
class JPSPath
{
public:
	JPSPath(World* p_world);
	~JPSPath();

	std::vector<Tile*> FindPath(Tile* p_currentTile, Tile* p_targetTile);
	void Recalculate();
	void Draw();

private:

	bool m_initialized;
	void Initialize(Tile* p_currentTile, Tile* p_targetTile);
	PathFindNode* ExpandNode(PathFindNode* p_cur, Vector2<int> p_direction);

	std::vector< Tile* > RecursivePathFinding();
	std::vector< Tile* > m_tilesInPath;

	bool HasForcedNeighbours(PathFindNode* p_node);
	PathFindNode* GetNodeAt(Vector2<int> p_gridPos);
	PathFindNode* m_startingNode;
	PathFindNode* m_currentNode;
	PathFindNode* m_goalNode;

	std::map<std::pair<int, int>, PathFindNode*> m_nodes;
	std::vector < PathFindNode*> m_openNodes;
	std::vector < PathFindNode*> m_closedNodes;
	std::vector < PathFindNode*> m_nodesInPath;
	std::vector < PathFindNode*> AdjacentNodes(PathFindNode* p_cur, bool p_considerDiagonallyAdjacent);

	DrawManager* m_drawManager;
};

