#include "stdafx.h"
#include "GridMap.h"

#include "Tile.h"

#include <ctime>
#include "Config.h"


GridMap::GridMap()
{
	m_rows = Config::ROWS;
	m_columns = Config::COLUMNS;
	m_tileSize = Config::TILE_SIZE;
}


GridMap::~GridMap()
{
	for (auto t : m_tiles) {
		delete t.second;
		t.second = nullptr;
	}
	m_tiles.clear();
	
}

void GridMap::Initialise()
{
	for (int x = 0; x < m_columns; x++)
	{
		for (int y = 0; y < m_rows; y++)
		{
			Tile* tile = new Tile(x*m_tileSize, y*m_tileSize, m_tileSize, m_tileSize, x,y);
			m_tiles[std::make_pair(x, y)] = tile;
			//m_tiles[Vector2<int>(x, y)] = tile;
		
		}
	}
	srand(time(NULL));

}

void GridMap::DrawGrid(Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a)
{
	for(auto t:m_tiles)
	{
		t.second->Draw(p_r, p_g, p_b, p_a);
	}
	
}

int GridMap::GetWidth()
{
	return m_columns*m_tileSize;
}

int GridMap::GetHeight()
{
	return m_rows*m_tileSize;
}

Tile* GridMap::GetTile(int p_gridX, int p_gridY)
{
	if(p_gridX<0||p_gridX>Config::COLUMNS-1||p_gridY<0||p_gridY>Config::ROWS-1)
	{
		return nullptr;
	}
	return	m_tiles[std::make_pair(p_gridX, p_gridY)];
	//return m_tiles[Vector2<int>(p_gridX, p_gridY)];
	
}




void GridMap::Update(float p_delta)
{
	for(auto t:m_tiles)
	{
	
		t.second->Update(p_delta);

	}

}
