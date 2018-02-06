#pragma once
#include <vector>
#include <map>
#include "Config.h"


class Tile;

class GridMap //TODO: make the gridmap an abstact class and derive a world class from it

{
public:
	GridMap();
	~GridMap();
	void Initialise();
	void DrawGrid(Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a);
	void Update(float p_delta);
	int GetWidth();
	int GetHeight();
	Tile* GetTile(int p_gridX, int p_gridY);

private:
	unsigned int m_rows;
	unsigned int m_columns;
	unsigned int m_tileSize;



	std::map<std::pair<int, int>, Tile*>m_tiles;
	//std::map<Vector2<int>, Tile*> m_tiles;
	int m_IDCounter = 1;

};

