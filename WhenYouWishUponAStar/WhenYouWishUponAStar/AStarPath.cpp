#include "stdafx.h"
#include "AStarPath.h"
#include "PathFindNode.h"
#include "Tile.h"
#include "World.h"
#include "ServiceLocator.h"
#include "DrawManager.h"
#include <algorithm>
#include <iostream>

AStarPath::AStarPath(World* p_world)
{
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	//Create a node at each tile in the world
	for(auto t: p_world->GetTiles())
	{
		m_nodes.insert(std::pair<std::pair<int,int>,PathFindNode*>(t.first, new PathFindNode(t.second)));
	}

	m_initialized = false;
}


AStarPath::~AStarPath()
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

std::vector< Tile* > AStarPath::FindPath(Tile* p_currentTile, Tile* p_targetTile)
{
	if(!m_initialized)
	{
		Initialize(p_currentTile, p_targetTile);
		m_currentNode = m_startingNode;
	}
	
	return RecursivePathFinding();

}

void AStarPath::Recalculate()
{

	m_initialized = false;
}

void AStarPath::Draw()
{
	if (m_initialized) {

		for (auto c : m_closedNodes) {
			m_drawManager->DrawRect(*c->m_tile->GetRect(), 255, 0, 0, 255);

			//	m_drawManager->DrawText(c->m_tile->GetWorldPos().x,c->m_tile->GetWorldPos().y, 12, std::to_string(c->GetFCost()), SDL_Color{ 255,255,255,255 });
			//	m_drawManager->DrawText(c->m_tile->GetWorldPos().x + 16, c->m_tile->GetWorldPos().y, 12, std::to_string(c->m_gCost), SDL_Color{ 0,255,0,255 });
			//	m_drawManager->DrawText(c->m_tile->GetWorldPos().x, c->m_tile->GetWorldPos().y + 16, 12, std::to_string(c->m_hCost), SDL_Color{ 255,255,0,255 });

		}
		for (auto o : m_openNodes) {
			m_drawManager->DrawRect(*o->m_tile->GetRect(), 0, 255, 0, 255);

			//	m_drawManager->DrawText(o->m_tile->GetWorldPos().x, o->m_tile->GetWorldPos().y, 12, std::to_string(o->GetFCost()), SDL_Color{ 255,255,255,255 });
			//	m_drawManager->DrawText(o->m_tile->GetWorldPos().x+16, o->m_tile->GetWorldPos().y, 12, std::to_string(o->m_gCost), SDL_Color{ 0,255,0,255 });
			//	m_drawManager->DrawText(o->m_tile->GetWorldPos().x , o->m_tile->GetWorldPos().y+16, 12, std::to_string(o->m_hCost), SDL_Color{ 255,255,0,255 });

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

void AStarPath::Initialize(Tile* p_currentTile, Tile* p_targetTile)
{
	//clear vectors
	m_openNodes.clear();

	m_closedNodes.clear();

	m_tilesInPath.clear();

	m_nodesInPath.clear();
	

	//set starting and goal nodes by comparing the tiles
	for(auto n:m_nodes)
	{
		if (n.second->m_tile == p_currentTile)
		{
			m_startingNode = n.second;
		}
		if(n.second->m_tile==p_targetTile)
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


std::vector< Tile* > AStarPath::RecursivePathFinding()
{

	if (m_currentNode == m_goalNode)
	{
		//set the current node's parent to the goal's parent for readability in the following for loop
		m_goalNode->m_parentNode = m_currentNode->m_parentNode;

		//build and return path
		for(PathFindNode * path = m_goalNode; path!=nullptr; path=path->m_parentNode)
		{
			m_nodesInPath.push_back(path);
			m_tilesInPath.push_back(path->m_tile);
		}
		return m_tilesInPath;
		
	}

	else {
		int lowestF = 99999;
		int nodeIndex = -1;

		//init adjacent node variables and add the nodes to the open list
		for (auto a: AdjacentNodes(m_currentNode))
		{
			
			if (std::find(m_openNodes.begin(), m_openNodes.end(), a) != m_openNodes.end() || std::find(m_closedNodes.begin(), m_closedNodes.end(), a) != m_closedNodes.end()) {
				//ignore nodes already in the closed and open lists
			}
			else if (a->m_tile->IsBlocked() == false)
			{

				a->m_parentNode = m_currentNode;
				//check if the node is adjacent orthogonally or diagonally by checking the manhattan dist, 1=ortho, 2=diagonal
				if(Manhattan(m_currentNode->m_tile->GetGridPos(), a->m_tile->GetGridPos())==1)
				{
					a->m_gCost = m_currentNode->m_gCost + 10;
				}
				else if (Manhattan(m_currentNode->m_tile->GetGridPos(), a->m_tile->GetGridPos()) == 2)
				{
					a->m_gCost = m_currentNode->m_gCost + 14;
				}

				
				a->m_hCost = Manhattan(a->m_tile->GetGridPos(), m_goalNode->m_tile->GetGridPos())*10;
				m_openNodes.push_back(a);
			}
			
		}
		//move current to closed list
		m_closedNodes.push_back(m_currentNode);
		m_openNodes.erase(std::remove(m_openNodes.begin(), m_openNodes.end(), m_currentNode), m_openNodes.end());

		if (m_openNodes.empty() == false) {

			//loop open list, select node with lowest F
			for (unsigned int i = 0; i < m_openNodes.size(); i++)
			{
				if (m_openNodes[i]->GetFCost() < lowestF)
				{
					lowestF = m_openNodes[i]->GetFCost();
					nodeIndex = i;
				}
			}

			//set current to best node
			m_currentNode = m_openNodes[nodeIndex];

			//recurse
			return RecursivePathFinding();
		}
		//no valid path found to target
		return {};
	}
}

std::vector<PathFindNode*> AStarPath::AdjacentNodes(PathFindNode* p_cur)
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
	if (p_cur->m_tile->GetGridPos().x> 0 && p_cur->m_tile->GetGridPos().y> 0)
	{
		adjacentNodes.push_back(m_nodes[std::make_pair(p_cur->m_tile->GetGridPos().x - 1, p_cur->m_tile->GetGridPos().y-1)]);
	}
	if (p_cur->m_tile->GetGridPos().x> 0 && p_cur->m_tile->GetGridPos().y< Config::ROWS - 1)
	{
		adjacentNodes.push_back(m_nodes[std::make_pair(p_cur->m_tile->GetGridPos().x - 1, p_cur->m_tile->GetGridPos().y + 1)]);
	}
	if (p_cur->m_tile->GetGridPos().x< Config::COLUMNS - 1 && p_cur->m_tile->GetGridPos().y> 0)
	{
		adjacentNodes.push_back(m_nodes[std::make_pair(p_cur->m_tile->GetGridPos().x + 1, p_cur->m_tile->GetGridPos().y - 1)]);
	}
	if (p_cur->m_tile->GetGridPos().x< Config::COLUMNS - 1 && p_cur->m_tile->GetGridPos().y< Config::ROWS - 1)
	{
		adjacentNodes.push_back(m_nodes[std::make_pair(p_cur->m_tile->GetGridPos().x + 1, p_cur->m_tile->GetGridPos().y+1)]);
	}
	
	return adjacentNodes;
}
