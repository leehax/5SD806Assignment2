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
	srand(time(NULL));

	for (int x = 0; x < m_columns; x++)
	{
		for (int y = 0; y < m_rows; y++)
		{
			Tile* tile = new Tile(x*m_tileSize, y*m_tileSize, m_tileSize, m_tileSize, x, y, rand()%3);
			m_tiles[std::make_pair(x, y)] = tile;

		}
	}

	m_ship = new Spaceship(GetTile(rand()%m_columns,rand()%m_rows)); 
	m_guiButtons.push_back(std::make_shared<GuiButton>(Config::TILE_SIZE * 3, Config::WINDOW_HEIGHT - 48, "Dirt","../External/textures/Spacedirt.png"));
	m_guiButtons.push_back(std::make_shared<GuiButton>(Config::TILE_SIZE * 6, Config::WINDOW_HEIGHT - 48, "Grass", "../External/textures/SpaceGrass.png"));
	m_guiButtons.push_back(std::make_shared<GuiButton>(Config::TILE_SIZE * 9, Config::WINDOW_HEIGHT - 48, "Crater", "../External/textures/Crater.png"));
	m_guiButtons.push_back(std::make_shared<GuiButton>(Config::TILE_SIZE * 12, Config::WINDOW_HEIGHT - 48, "Ship", "../External/textures/Spaceship.png"));
	m_guiButtons.push_back(std::make_shared<GuiButton>(Config::TILE_SIZE * 15, Config::WINDOW_HEIGHT - 48, "TrPost", "../External/textures/TradingPost.png"));
	m_guiButtons.push_back(std::make_shared<GuiButton>(Config::TILE_SIZE * 18, Config::WINDOW_HEIGHT - 48, "FallenStar", "../External/textures/FallenStar.png"));
	m_guiButtons.push_back(std::make_shared<GuiButton>(Config::TILE_SIZE * 21, Config::WINDOW_HEIGHT - 48, "StarChaser", "../External/textures/StarChaser.png"));
	m_activeSpawnButton = m_guiButtons[0];
}

void World::DrawGrid(Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a)
{
	for (auto t : m_tiles)
	{
		t.second->Draw(p_r, p_g, p_b, p_a);
	}
	m_ship->Draw();
	for(auto g:m_guiButtons)
	{
		g->Draw();
	}
}

void World::Update(float p_delta)
{
	for (auto t : m_tiles)
	{

		t.second->Update(p_delta);

	}
	for(auto g:m_guiButtons)
	{
		if(g!=m_activeSpawnButton)
		{
			g->SetActive(false);
		}
		else if(g==m_activeSpawnButton)
		{
			g->SetActive(true);
		}
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
			if (p_ev.type == SDL_MOUSEBUTTONDOWN&&p_ev.button.button == SDL_BUTTON_LEFT)
			{
				t.second->OnClick(m_activeSpawnButton->GetName());
				
			}
		}
	}

	for(auto g:m_guiButtons)
	{
		if (SDL_PointInRect(&p_pos, g->GetRect()))
		{
			if (p_ev.type == SDL_MOUSEBUTTONDOWN&&p_ev.button.button==SDL_BUTTON_LEFT)
			{
				//g->SetActive(true);
				m_activeSpawnButton = g;
				
		
			}
		}
	}
	
}
