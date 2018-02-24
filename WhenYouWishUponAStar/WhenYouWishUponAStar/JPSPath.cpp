#include "stdafx.h"
#include "JPSPath.h"
#include "DrawManager.h"
#include "ServiceLocator.h"
#include "World.h"
#include "PathFindNode.h"
#include "Config.h"
#include "Tile.h"
#include <algorithm>

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
	for (unsigned int i = 0; i<m_openNodes.size(); i++)
	{
		delete m_openNodes[i];
		m_openNodes[i] = nullptr;
	}
	m_openNodes.clear();

	for (unsigned int i = 0; i<m_closedNodes.size(); i++)
	{
		delete m_closedNodes[i];
		m_closedNodes[i] = nullptr;
	}
	m_closedNodes.clear();
	for (unsigned int i = 0; i < m_tilesInPath.size(); i++)
	{
		delete m_tilesInPath[i];
		m_tilesInPath[i] = nullptr;
	}
	m_tilesInPath.clear();
}


void JPSPath::FindSuccessors(PathFindNode* p_node)
{

	for(auto a: AdjacentNodes(p_node))
	{
		PathFindNode* successor = Jump(a, p_node);
		if(successor)
		{
			
			if(std::find(m_closedNodes.begin(),m_closedNodes.end(),successor) != m_closedNodes.end())
			{
					continue;
			}
			bool inOpenList = std::find(m_openNodes.begin(), m_openNodes.end(), successor) != m_openNodes.end();

			if( !inOpenList)
			{
				successor->m_gCost = p_node->m_gCost + Manhattan(p_node->GetGridPos(), successor->GetGridPos());
				successor->m_hCost = Manhattan(successor->GetGridPos(), m_goalNode->GetGridPos());
				successor->m_parentNode = p_node;
				m_openNodes.push_back(successor);
			}
		}
	}
}

PathFindNode* JPSPath::Jump(PathFindNode* p_cur, PathFindNode* p_parent)
{
	if(p_cur==nullptr)
	{
		return nullptr;
	}
	int x = p_cur->GetGridPos().x;
	int y = p_cur->GetGridPos().y;

	Vector2<int> direction = p_cur->GetGridPos() - p_parent->GetGridPos();

	if (BlockedNodeAt(x,y))
	{
		return nullptr;
	}
	if (p_cur == m_goalNode)
	{
		return p_cur;
	}

		
	if (direction.x != 0 && direction.y != 0) {

		if(  !BlockedNodeAt(x - direction.x, y + direction.y) && BlockedNodeAt(x - direction.x, y)
			|| !BlockedNodeAt(x + direction.x, y - direction.y) && BlockedNodeAt(x, y - direction.y))
		{
			return p_cur;
		}

		if(Jump(GetNodeAt(x + direction.x, y), p_cur) || Jump(GetNodeAt(x, y+direction.y), p_cur))
		{
			return p_cur;
		}

	}
	else
	{
		if (direction.x == 0) 
		{
			if (!BlockedNodeAt(x + 1, y + direction.y) && BlockedNodeAt(x + 1, y)
				|| !BlockedNodeAt(x - 1, y + direction.y) && BlockedNodeAt(x - 1, y))
			{
				return p_cur;
			}
		}
		else
		{
			if (!BlockedNodeAt(x + direction.x, y + 1) && BlockedNodeAt(x, y + 1)
				|| !BlockedNodeAt(x + direction.x, y - 1) && BlockedNodeAt(x, y - 1))
			{
				return p_cur;
			}
		}
		
	}


	return Jump(GetNodeAt(p_cur->GetGridPos() + direction), p_cur);
	
	
}


std::vector<Tile*> JPSPath::RecursivePathFinding()
{
	//expand adjacent nodes
	if(m_currentNode==m_goalNode)
	{

		//set the current node's parent to the goal's parent for readability in the following for loop
		m_goalNode->m_parentNode = m_currentNode->m_parentNode;

		//build and return path
		for (PathFindNode * path = m_goalNode; path != nullptr; path = path->m_parentNode)
		{
			m_nodesInPath.push_back(path);
			m_tilesInPath.push_back(path->m_tile);
		}
		return m_tilesInPath;
	}
	else {

		FindSuccessors(m_currentNode);

		int lowestF = 99999;
		int nodeIndex = -1;

		m_closedNodes.push_back(m_currentNode);
		m_openNodes.erase(std::remove(m_openNodes.begin(), m_openNodes.end(), m_currentNode), m_openNodes.end());

		if (m_openNodes.empty() == false) {

			//loop open list, select node with lowest F
			for (unsigned int i = 0; i < m_openNodes.size(); i++)
			{
				if (m_openNodes[i]->GetFCost(false) < lowestF)
				{
					lowestF = m_openNodes[i]->GetFCost(false);
					nodeIndex = i;
				}
			}

			//set current to best node
			m_currentNode = m_openNodes[nodeIndex];

			//recurse
			return RecursivePathFinding();
		}

		
	}
	return {};
}


std::vector<PathFindNode*> JPSPath::AdjacentNodes(PathFindNode* p_node)
{
	std::vector<PathFindNode*> adjacentNodes;

	int x = p_node->GetGridPos().x;
	int y = p_node->GetGridPos().y;
	
	if(p_node->m_parentNode) //the node has a parent, we only return the relevant neighbors in the direction
	{
		Vector2<int> direction; //set the x and y components to be at max a value of 1, as the parent doesnt have to be adjacent
		direction.x = (x - p_node->m_parentNode->GetGridPos().x) / std::max(std::abs(x - p_node->m_parentNode->GetGridPos().x), 1);
		direction.y = (y - p_node->m_parentNode->GetGridPos().y) / std::max(std::abs(y - p_node->m_parentNode->GetGridPos().y), 1);

		if(direction.x != 0 && direction.y != 0) //diagonal
		{
			//natural neighbors
			if ( !BlockedNodeAt(x + direction.x, y))
			{
				adjacentNodes.push_back(GetNodeAt(x + direction.x, y));
			}

			if( !BlockedNodeAt(x, y + direction.y))
			{
				adjacentNodes.push_back(GetNodeAt(x, y + direction.y));
			}
			if ( !BlockedNodeAt(x + direction.x, y + direction.y))
			{
				adjacentNodes.push_back(GetNodeAt(x + direction.x, y + direction.y));
			}

			//forced neighbors
			if ( BlockedNodeAt(x - direction.x, y))
			{
				adjacentNodes.push_back(GetNodeAt(x - direction.x, y + direction.y));
			}

			if ( BlockedNodeAt(x, y - direction.y))
			{
				adjacentNodes.push_back(GetNodeAt(x + direction.x, y - direction.y));
			}

		}
		else //orthogonal
		{
			if(direction.x == 0) //vertical
			{
				//natural neighbor
				if( !BlockedNodeAt(x,y+direction.y))
				{
					adjacentNodes.push_back(GetNodeAt(x, y + direction.y));
				}

				//forced neighbors
				if ( BlockedNodeAt(x + 1, y))
				{
					adjacentNodes.push_back(GetNodeAt(x + 1, y + direction.y));
				}
				if ( BlockedNodeAt(x - 1, y))
				{
					adjacentNodes.push_back(GetNodeAt(x - 1, y + direction.y));
				}

			}
			else //horizontal
			{
				//natural neighbor
				if ( !BlockedNodeAt(x + direction.x, y))
				{
					adjacentNodes.push_back(GetNodeAt(x + direction.x , y));
				}
				
				//forced neighbors
				if ( BlockedNodeAt(x, y + 1))
				{
					adjacentNodes.push_back(GetNodeAt(x +direction.x, y + 1));
				}
				if ( BlockedNodeAt(x, y - 1))
				{
					adjacentNodes.push_back(GetNodeAt(x + direction.x, y - 1));
				}
			}
		}
	}


	else //we return all neighbors
	{
		//Orthogonal
		if (x > 0)
		{
			adjacentNodes.push_back(GetNodeAt(x - 1, y));
		}
		if (x < Config::COLUMNS - 1)
		{
			adjacentNodes.push_back(GetNodeAt(x + 1, y));
		}
		if (y > 0)
		{
			adjacentNodes.push_back(GetNodeAt(x, y - 1));
		}
		if (y < Config::ROWS - 1)
		{
			adjacentNodes.push_back(GetNodeAt(x, y + 1));
		}

		//Diagonal
		if (x > 0 && y > 0)
		{
			adjacentNodes.push_back(GetNodeAt(x - 1, y - 1));
		}
		if (x > 0 && y < Config::ROWS - 1)
		{
			adjacentNodes.push_back(GetNodeAt(x - 1, y + 1));
		}
		if (x < Config::COLUMNS - 1 && y> 0)
		{
			adjacentNodes.push_back(GetNodeAt(x + 1, y - 1));
		}
		if (x < Config::COLUMNS - 1 && y < Config::ROWS - 1)
		{
			adjacentNodes.push_back(GetNodeAt(x + 1, y + 1));

		}
		
	}

	return adjacentNodes;
}
