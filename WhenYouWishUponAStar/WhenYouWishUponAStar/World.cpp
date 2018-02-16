#include "stdafx.h"
#include "World.h"
#include <ctime>
#include "Tile.h"
#include "StarChaser.h"
#include "Spaceship.h"
#include "GuiButton.h"
#include <iostream>

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
			Tile* tile = new Tile(x*m_tileSize, y*m_tileSize, m_tileSize, m_tileSize, x, y);
			m_tiles[std::make_pair(x, y)] = tile;

		}
	}

	 
	m_ship = std::make_shared<Spaceship>(GetTile(rand() % m_columns, rand() % m_rows));
	m_starchsr = std::make_shared<StarChaser>(GetTile(rand() % m_columns, rand() % m_rows));
	m_entities.push_back(m_ship);
	m_entities.push_back(m_starchsr);
	m_guiButtons.push_back(std::make_shared<GuiButton>(Config::TILE_SIZE * 2, Config::WINDOW_HEIGHT - 48, "Dirt","../External/textures/Spacedirt.png"));
	m_guiButtons.push_back(std::make_shared<GuiButton>(Config::TILE_SIZE * 4, Config::WINDOW_HEIGHT - 48, "Grass", "../External/textures/SpaceGrass.png"));
	m_guiButtons.push_back(std::make_shared<GuiButton>(Config::TILE_SIZE * 6, Config::WINDOW_HEIGHT - 48, "Crater", "../External/textures/Crater.png"));
	m_guiButtons.push_back(std::make_shared<GuiButton>(Config::TILE_SIZE * 8, Config::WINDOW_HEIGHT - 48, "Ship", "../External/textures/Spaceship.png"));
	m_guiButtons.push_back(std::make_shared<GuiButton>(Config::TILE_SIZE * 10, Config::WINDOW_HEIGHT - 48, "TrPost", "../External/textures/TradingPost.png"));
	m_guiButtons.push_back(std::make_shared<GuiButton>(Config::TILE_SIZE * 12, Config::WINDOW_HEIGHT - 48, "FllnStar", "../External/textures/Star.png"));
	m_guiButtons.push_back(std::make_shared<GuiButton>(Config::TILE_SIZE * 14, Config::WINDOW_HEIGHT - 48, "StarChsr", "../External/textures/StarChaser.png"));
	m_guiButtons.push_back(std::make_shared<GuiButton>(Config::TILE_SIZE * 16, Config::WINDOW_HEIGHT - 48, "Block", "../External/textures/BlockedTile.png"));

	m_activeSpawnButton = m_guiButtons[0];
}

void World::DrawGrid(Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a)
{
	for (auto t : m_tiles)
	{
		t.second->Draw(p_r, p_g, p_b, p_a);
	}
	
	for(auto g:m_guiButtons)
	{
		g->Draw();
	}
	for(auto e:m_entities)
	{
		e->Draw();
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
	for (auto e : m_entities)
	{
		e->Update(p_delta);
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
				if (m_activeSpawnButton->GetName() == "Dirt" || m_activeSpawnButton->GetName() == "Grass" ||
					m_activeSpawnButton->GetName() == "Crater" ) {
					t.second->OnClick(m_activeSpawnButton->GetName());
				}
				else if(m_activeSpawnButton->GetName() == "Block")
				{
					for(auto e:m_entities)
					{
						if(e->GetCurrentTile()!=t.second)
						{
							t.second->OnClick(m_activeSpawnButton->GetName());
						}
					}
				}
				else if(m_activeSpawnButton->GetName() == "Ship")
				{
					
						if(m_ship)
						{
							m_ship->SetCurTile(t.second);
						}
						else if (m_ship==nullptr)
						{
							m_ship = std::make_shared<Spaceship>(t.second);
						}
					
				}
				else if(m_activeSpawnButton->GetName() == "StarChsr")
				{
					for (auto e : m_entities)
					{
						if (e->GetType() == "StarChsr")
						{
							e->SetCurTile(t.second);
						}
					}
				}
				
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

std::vector<Tile*> World::GetTiles()
{
	std::vector<Tile*> tiles;
	for(auto t:m_tiles)
	{
		tiles.push_back(t.second);
	}
	return tiles;
}


