#include "stdafx.h"
#include "World.h"
#include <ctime>
#include "Tile.h"
#include "StarChaser.h"
#include "Spaceship.h"
#include "GuiButton.h"
#include "FallenStar.h"
#include "TradingPost.h"
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

	for (unsigned int x = 0; x < m_columns; x++)
	{
		for (unsigned int y = 0; y < m_rows; y++)
		{
			Tile* tile = new Tile(x*m_tileSize, y*m_tileSize, m_tileSize, m_tileSize, x, y);
			m_tiles[std::make_pair(x, y)] = tile;

		}
	}

	 


;
	m_ship = std::make_unique<Spaceship>();
	m_ship->SetCurTile(GetTile(rand() % m_columns, rand() % m_rows));

	m_fallenStar = std::make_unique<FallenStar>();
	m_fallenStar->SetCurTile(GetTile(rand() % m_columns, rand() % m_rows));

	m_tradingPost= std::make_unique<TradingPost>();
	m_tradingPost->SetCurTile(GetTile(rand() % m_columns, rand() % m_rows));

	m_starChaser = std::make_unique<StarChaser>(this);
	m_starChaser->SetCurTile(GetTile(rand() % m_columns, rand() % m_rows));
	m_starChaser->SetState("Collect");
	
	

	m_guiButtons.push_back(std::make_shared<GuiButton>(Config::TILE_SIZE, Config::WINDOW_HEIGHT - 48, "Dirt","../External/textures/Spacedirt.png"));
	m_guiButtons.push_back(std::make_shared<GuiButton>(Config::TILE_SIZE * 4, Config::WINDOW_HEIGHT - 48, "Grass", "../External/textures/SpaceGrass.png"));
	m_guiButtons.push_back(std::make_shared<GuiButton>(Config::TILE_SIZE * 7, Config::WINDOW_HEIGHT - 48, "Crater", "../External/textures/Crater.png"));
	m_guiButtons.push_back(std::make_shared<GuiButton>(Config::TILE_SIZE * 10, Config::WINDOW_HEIGHT - 48, "Ship", "../External/textures/Spaceship.png"));
	m_guiButtons.push_back(std::make_shared<GuiButton>(Config::TILE_SIZE * 13, Config::WINDOW_HEIGHT - 48, "TrPost", "../External/textures/TradingPost.png"));
	m_guiButtons.push_back(std::make_shared<GuiButton>(Config::TILE_SIZE * 16, Config::WINDOW_HEIGHT - 48, "FllnStar", "../External/textures/Star.png"));
	m_guiButtons.push_back(std::make_shared<GuiButton>(Config::TILE_SIZE * 19, Config::WINDOW_HEIGHT - 48, "StarChsr", "../External/textures/StarChaser.png"));
	m_guiButtons.push_back(std::make_shared<GuiButton>(Config::TILE_SIZE * 22, Config::WINDOW_HEIGHT - 48, "Block", "../External/textures/BlockedTile.png"));

	m_selectedGuiButton = m_guiButtons[0];
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
	m_ship->Draw();
	m_starChaser->Draw();
	m_fallenStar->Draw();
	m_tradingPost->Draw();
}

void World::Update(float p_delta)
{
	for (auto t : m_tiles)
	{

		t.second->Update(p_delta);

	}
	for(auto g:m_guiButtons)
	{
		if(g!=m_selectedGuiButton)
		{
			g->SetActive(false);
		}
		else if(g==m_selectedGuiButton)
		{
			g->SetActive(true);
		}
	}
	m_ship->Update(p_delta);
	m_starChaser->Update(p_delta);
	m_fallenStar->Update(p_delta);
	m_tradingPost->Update(p_delta);

	
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
				

				if (m_selectedGuiButton->GetName() == "Dirt" || m_selectedGuiButton->GetName() == "Grass" ||
					m_selectedGuiButton->GetName() == "Crater" ) {
					t.second->OnClick(m_selectedGuiButton->GetName());
				}
				else if(m_selectedGuiButton->GetName() == "Block")
				{
					if(EntityOnTile(t.second)==false)
					{
						t.second->SetBlocked(true);
					
					
					}
				}
				else if (m_selectedGuiButton->GetName() == "Ship")
				{

					if (m_ship)
					{
						m_ship->SetCurTile(t.second);
					}


				}
				else if (m_selectedGuiButton->GetName() == "StarChsr")
				{

					if (m_starChaser)
					{
						m_starChaser->SetCurTile(t.second);
					
					
					}


				}
				else if (m_selectedGuiButton->GetName() == "FllnStar")
				{

					if (m_fallenStar)
					{
						m_fallenStar->SetCurTile(t.second);
					}


				}
				else if (m_selectedGuiButton->GetName() == "TrPost")
				{

					if (m_tradingPost)
					{
						m_tradingPost->SetCurTile(t.second);
					}


				}
				m_starChaser->RecalculatePath();
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
				m_selectedGuiButton = g;
				
		
			}
		}
	}
	
}

std::map<std::pair<int, int>, Tile*> World::GetTiles()
{
	return m_tiles;
}

bool World::EntityOnTile(Tile* p_tile)
{
	return m_ship->GetCurrentTile() == p_tile || m_starChaser->GetCurrentTile() == p_tile || m_fallenStar->GetCurrentTile() == p_tile || m_tradingPost->GetCurrentTile() == p_tile;
}

Tile* World::GetTileWithEntity(const std::string p_type)
{
	if(p_type=="FllnStar")
	{
		return m_fallenStar->GetCurrentTile();
	}
	else if(p_type=="TrPost")
	{
		return m_ship->GetCurrentTile();
	}
	else if(p_type=="Ship")
	{
		return m_ship->GetCurrentTile();
	}
	else if(p_type=="StarChsr")
	{
		return m_starChaser->GetCurrentTile();
	}

	return nullptr;
}


