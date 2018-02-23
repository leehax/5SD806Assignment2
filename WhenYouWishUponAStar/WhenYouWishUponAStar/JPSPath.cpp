#include "stdafx.h"
#include "JPSPath.h"
#include "DrawManager.h"
#include "ServiceLocator.h"
#include "World.h"
#include "PathFindNode.h"
#include "Config.h"
#include "Tile.h"
JPSPath::JPSPath(World* p_world)
{

	m_drawManager = ServiceLocator<DrawManager>::GetService();
	//Create a node at each tile in the world
	for (auto t : p_world->GetTiles())
	{
		m_nodes.insert(std::pair<std::pair<int, int>, PathFindNode*>(t.first, new PathFindNode(t.second)));
	}

	m_initialized = false;
}


JPSPath::~JPSPath()
{
}

std::vector<Tile*> JPSPath::FindPath(Tile* p_currentTile, Tile* p_targetTile)
{
	if (!m_initialized)
	{
		Initialize(p_currentTile, p_targetTile);
		m_currentNode = m_startingNode;
	}

	return RecursivePathFinding();
}

void JPSPath::Recalculate()
{
	m_initialized = false;
}

void JPSPath::Draw()
{
	if (m_initialized) {

		for (auto c : m_closedNodes) {
			m_drawManager->DrawRect(*c->m_tile->GetRect(), 255, 0, 0, 255);

		}
		for (auto o : m_openNodes) {
			m_drawManager->DrawRect(*o->m_tile->GetRect(), 0, 255, 0, 255);
		}

		for (auto n : m_nodesInPath)
		{
			if (n->m_parentNode) {
				m_drawManager->DrawLine(n->m_tile->GetWorldPos().x + Config::HALF_TILE, n->m_tile->GetWorldPos().y + Config::HALF_TILE, n->m_parentNode->m_tile->GetWorldPos().x + Config::HALF_TILE, n->m_parentNode->m_tile->GetWorldPos().y + Config::HALF_TILE, 0, 255, 255, 255);
			}
		}
		m_drawManager->DrawRect(*m_currentNode->m_tile->GetRect(), 255, 255, 0, 255);
	}
}

void JPSPath::Initialize(Tile* p_currentTile, Tile* p_targetTile)
{
	//clear vectors
	m_openNodes.clear();

	m_closedNodes.clear();

	m_tilesInPath.clear();

	m_nodesInPath.clear();


	//set starting and goal nodes by comparing the tiles
	for (auto n : m_nodes)
	{
		if (n.second->m_tile == p_currentTile)
		{
			m_startingNode = n.second;
		}
		if (n.second->m_tile == p_targetTile)
		{
			m_goalNode = n.second;
		}
	}

	m_startingNode->m_gCost = 0;
	m_startingNode->m_hCost = Manhattan(m_startingNode->m_tile->GetGridPos(), m_goalNode->m_tile->GetGridPos());
	m_startingNode->m_parentNode = nullptr;

	m_openNodes.push_back(m_startingNode);

	m_initialized = true;
}

PathFindNode* JPSPath::ExpandNode(PathFindNode* p_cur, Vector2<int> p_direction)
{
	

	PathFindNode* nextNode = GetNodeAt(p_cur->GetGridPos() + p_direction);

	if (nextNode == nullptr)
	{
		return nullptr;
	}

	//m_openNodes.push_back(nextNode);
	if (nextNode == m_goalNode)
	{
		return nextNode;
	}
	if(HasForcedNeighbours(nextNode))
	{
		return nextNode;
	}
		
	if (p_direction.x != 0 && p_direction.y != 0) {

		Vector2<int> verticalDirection = Vector2<int>(0, p_direction.y);
		Vector2<int> horizontalDirection = Vector2<int>(p_direction.x, 0);
		std::vector<Vector2<int>> directions;
		directions.push_back(verticalDirection);
		directions.push_back(horizontalDirection);

		for (int i = 0; i < directions.size(); i++)
		{
			if (ExpandNode(nextNode, directions[i]) != nullptr)
			{
				return nextNode;
			}
		}

	}
	return ExpandNode(nextNode, p_direction);

}


std::vector<Tile*> JPSPath::RecursivePathFinding()
{
	//expand adjacent nodes
	for(auto a: AdjacentNodes(m_currentNode,true))
	{
		PathFindNode* successor=ExpandNode(a,  a->GetGridPos()- m_currentNode->GetGridPos());
		if (successor) {
			m_openNodes.push_back(successor);
		}
	}
	
	
	//if expansion finds a forced neighbor, add the node to the open list
	//recurse from nodes in open list


	//return path
	return {};
}

bool JPSPath::HasForcedNeighbours(PathFindNode* p_node)
{
	for(auto a: AdjacentNodes(p_node, false))
	{
		if(a->m_blocked())
		{
			//forced neighbor at p_cur.pos +direction + a.pos
			return true;
		}
	}
	return false;
}

PathFindNode* JPSPath::GetNodeAt(Vector2<int> p_gridPos)
{
	
		if (p_gridPos.x<0 || p_gridPos.x>Config::COLUMNS - 1 || p_gridPos.y<0 || p_gridPos.y>Config::ROWS - 1)
		{
			return nullptr;
		}
		return	m_nodes[std::make_pair(p_gridPos.x, p_gridPos.y)];
	
}

std::vector<PathFindNode*> JPSPath::AdjacentNodes(PathFindNode* p_cur, bool p_considerDiagonallyAdjacent)
{
	std::vector<PathFindNode*> adjacentNodes;

	//Orthogonally adjacent
	if(p_cur->m_tile->GetGridPos().x> 0)
	{
		adjacentNodes.push_back(m_nodes[std::make_pair(p_cur->m_tile->GetGridPos().x - 1, p_cur->m_tile->GetGridPos().y)]);
	}
	if (p_cur->m_tile->GetGridPos().x< Config::COLUMNS-1)
	{
		adjacentNodes.push_back(m_nodes[std::make_pair(p_cur->m_tile->GetGridPos().x + 1, p_cur->m_tile->GetGridPos().y)]);
	}
	if (p_cur->m_tile->GetGridPos().y> 0)
	{
		adjacentNodes.push_back(m_nodes[std::make_pair(p_cur->m_tile->GetGridPos().x , p_cur->m_tile->GetGridPos().y-1)]);
	}
	if (p_cur->m_tile->GetGridPos().y< Config::ROWS - 1)
	{
		adjacentNodes.push_back(m_nodes[std::make_pair(p_cur->m_tile->GetGridPos().x, p_cur->m_tile->GetGridPos().y+1)]);
	}
	//Diagonally adjacent
	if (p_considerDiagonallyAdjacent == true) {
		
		if (p_cur->m_tile->GetGridPos().x > 0 && p_cur->m_tile->GetGridPos().y > 0)
		{
			adjacentNodes.push_back(m_nodes[std::make_pair(p_cur->m_tile->GetGridPos().x - 1, p_cur->m_tile->GetGridPos().y - 1)]);
		}
		if (p_cur->m_tile->GetGridPos().x > 0 && p_cur->m_tile->GetGridPos().y < Config::ROWS - 1)
		{
			adjacentNodes.push_back(m_nodes[std::make_pair(p_cur->m_tile->GetGridPos().x - 1, p_cur->m_tile->GetGridPos().y + 1)]);
		}
		if (p_cur->m_tile->GetGridPos().x < Config::COLUMNS - 1 && p_cur->m_tile->GetGridPos().y> 0)
		{
			adjacentNodes.push_back(m_nodes[std::make_pair(p_cur->m_tile->GetGridPos().x + 1, p_cur->m_tile->GetGridPos().y - 1)]);
		}
		if (p_cur->m_tile->GetGridPos().x < Config::COLUMNS - 1 && p_cur->m_tile->GetGridPos().y < Config::ROWS - 1)
		{
			adjacentNodes.push_back(m_nodes[std::make_pair(p_cur->m_tile->GetGridPos().x + 1, p_cur->m_tile->GetGridPos().y + 1)]);
		}
	}

	return adjacentNodes;
}
