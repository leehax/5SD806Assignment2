#include "stdafx.h"
#include "World.h"
#include <ctime>
#include "Tile.h"

World::World()
{
	m_rows = Config::ROWS;
	m_columns = Config::COLUMNS;
	m_tileSize = Config::TILE_SIZE;
}


World::~World()
{
	for (auto t : m_tiles) {
		delete t.second;
		t.second = nullptr;
	}
	m_tiles.clear();

}

void World::Initialise()
{
	for (int x = 0; x < m_columns; x++)
	{
		for (int y = 0; y < m_rows; y++)
		{
			Tile* tile = new Tile(x*m_tileSize, y*m_tileSize, m_tileSize, m_tileSize, x, y, rand()%3);
			m_tiles[std::make_pair(x, y)] = tile;

		}
	}
	srand(time(NULL));
}

void World::DrawGrid(Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a)
{
	for (auto t : m_tiles)
	{
		t.second->Draw(p_r, p_g, p_b, p_a);
	}
}

void World::Update(float p_delta)
{
	for (auto t : m_tiles)
	{

		t.second->Update(p_delta);

	}
}

Tile* World::GetTile(int p_gridX, int p_gridY)
{
	if (p_gridX<0 || p_gridX>Config::COLUMNS - 1 || p_gridY<0 || p_gridY>Config::ROWS - 1)
	{
		return nullptr;
	}
	return	m_tiles[std::make_pair(p_gridX, p_gridY)];
}

void World::HandleEvent(SDL_Event& p_ev, SDL_Point p_pos)
{
	
	for(auto t:m_tiles)
	{
		if(SDL_PointInRect(&p_pos,t.second->GetRect()))
		{
			t.second->HandleButtonEvent(p_ev.button);
		}
	}
}
