#pragma once
#include <vector>
#include <memory>
class AStarNode;

class AStarPath
{
public:
	AStarPath();
	~AStarPath();

	std::vector < std::shared_ptr< AStarNode >> m_openNodes; //todo: implement linked list
	std::vector < std::shared_ptr< AStarNode >> m_closedNodes;

	void BuildPath(); //Recursive path finding func
};

