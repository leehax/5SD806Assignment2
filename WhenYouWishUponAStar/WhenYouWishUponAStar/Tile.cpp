#include "stdafx.h"
#include "Tile.h"
#include "DrawManager.h"

#include "ServiceLocator.h"
#include "GridMap.h"
#include "SpriteManager.h"
#include <iostream>

Tile::Tile(int p_x, int p_y, int p_w, int p_h, int p_gridX, int p_gridY)
{
	m_rect = { p_x,p_y,p_w,p_h };
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	m_spriteManager = ServiceLocator<SpriteManager>::GetService();
	m_sprite = m_spriteManager->CreateSprite("../External/Textures/DirtSprite.png", 0, 0, 24, 24);
	m_gridX = p_gridX;
	m_gridY = p_gridY;
	m_x = p_x;
	m_y = p_y;
	m_gridMap = ServiceLocator<GridMap>::GetService();
	m_lockedByType = "unlocked";
}

Tile::~Tile()
{
}

SDL_Rect* Tile::GetRect()
{
	return &m_rect;
}

void Tile::Draw(Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a)
{
	m_drawManager->Draw(m_sprite, m_x, m_y, 1);


	m_drawManager->DrawRect(m_rect, p_r, p_g, p_b, p_a);

}



void Tile::Update(float p_delta)
{


	
}

void Tile::FindNeighbours()
{
	
	if(m_gridMap->GetTile(m_gridX - 1, m_gridY - 1))
	{
		m_neighbours.push_back(m_gridMap->GetTile(m_gridX - 1, m_gridY - 1));
	}

	if(m_gridMap->GetTile(m_gridX, m_gridY - 1))
	{
		m_neighbours.push_back(m_gridMap->GetTile(m_gridX, m_gridY - 1));
	}
	
	if(m_gridMap->GetTile(m_gridX + 1, m_gridY - 1))
	{
		m_neighbours.push_back(m_gridMap->GetTile(m_gridX + 1, m_gridY - 1));
	}


	if (m_gridMap->GetTile(m_gridX - 1, m_gridY))
	{
		m_neighbours.push_back(m_gridMap->GetTile(m_gridX - 1, m_gridY));
	}
	
	if (m_gridMap->GetTile(m_gridX + 1, m_gridY))
	{
		m_neighbours.push_back(m_gridMap->GetTile(m_gridX + 1, m_gridY));
	}
	
	if (m_gridMap->GetTile(m_gridX - 1, m_gridY + 1))
	{
		m_neighbours.push_back(m_gridMap->GetTile(m_gridX - 1, m_gridY + 1));
	}
	
	if (m_gridMap->GetTile(m_gridX, m_gridY + 1))
	{
		m_neighbours.push_back(m_gridMap->GetTile(m_gridX, m_gridY + 1));
	}

	if (m_gridMap->GetTile(m_gridX + 1, m_gridY + 1))
	{
		m_neighbours.push_back(m_gridMap->GetTile(m_gridX + 1, m_gridY + 1));
	}

	
	

}

std::vector<Tile*> Tile::GetNeighbours()
{
	return m_neighbours;
}


Vector2<int> Tile::GetWorldPos()
{
	return Vector2<int>(m_x, m_y);
}

Vector2<int> Tile::GetGridPos()
{
	if (this) {
		return Vector2<int>(m_gridX, m_gridY);
	}
	return Vector2<int>();
}



void Tile::Lock(int p_ID, std::string p_type)
{


}

void Tile::Unlock(int p_ID, std::string p_type)
{
	if(p_ID == m_lockedByID&&p_type==m_lockedByType)
	{
		m_lockedByType = "unlocked";
	}
}


bool Tile::Locked(int p_ID, std::string p_type)
{
	if(p_type != m_lockedByType)
	{
		return false;
	}
	else
	{
		return m_lockedByID != p_ID;
	}
}





