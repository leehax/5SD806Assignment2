#include "stdafx.h"
#include "Tile.h"
#include "DrawManager.h"

#include "ServiceLocator.h"
#include "World.h"
#include "SpriteManager.h"
#include <iostream>


Tile::Tile(int p_x, int p_y, int p_w, int p_h, int p_gridX, int p_gridY)
{
	m_rect = { p_x,p_y,p_w,p_h };
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	m_spriteManager = ServiceLocator<SpriteManager>::GetService();
	m_sprites.push_back(m_spriteManager->CreateSprite("../External/Textures/SpaceDirt.png", 0, 0, 32, 32));
	m_sprites.push_back(m_spriteManager->CreateSprite("../External/Textures/Crater.png", 0, 0, 32, 32));


	m_activeSprite = m_sprites[0];
	m_gridX = p_gridX;
	m_gridY = p_gridY;
	m_x = p_x;
	m_y = p_y;
	m_world = ServiceLocator<World>::GetService();

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
	m_drawManager->Draw(m_activeSprite, m_x, m_y, 1);


	m_drawManager->DrawRect(m_rect, p_r, p_g, p_b, p_a);

}



void Tile::Update(float p_delta)
{


	
}

void Tile::FindNeighbours()
{
	
	if(m_world->GetTile(m_gridX - 1, m_gridY - 1))
	{
		m_neighbours.push_back(m_world->GetTile(m_gridX - 1, m_gridY - 1));
	}

	if(m_world->GetTile(m_gridX, m_gridY - 1))
	{
		m_neighbours.push_back(m_world->GetTile(m_gridX, m_gridY - 1));
	}
	
	if(m_world->GetTile(m_gridX + 1, m_gridY - 1))
	{
		m_neighbours.push_back(m_world->GetTile(m_gridX + 1, m_gridY - 1));
	}


	if (m_world->GetTile(m_gridX - 1, m_gridY))
	{
		m_neighbours.push_back(m_world->GetTile(m_gridX - 1, m_gridY));
	}
	
	if (m_world->GetTile(m_gridX + 1, m_gridY))
	{
		m_neighbours.push_back(m_world->GetTile(m_gridX + 1, m_gridY));
	}
	
	if (m_world->GetTile(m_gridX - 1, m_gridY + 1))
	{
		m_neighbours.push_back(m_world->GetTile(m_gridX - 1, m_gridY + 1));
	}
	
	if (m_world->GetTile(m_gridX, m_gridY + 1))
	{
		m_neighbours.push_back(m_world->GetTile(m_gridX, m_gridY + 1));
	}

	if (m_world->GetTile(m_gridX + 1, m_gridY + 1))
	{
		m_neighbours.push_back(m_world->GetTile(m_gridX + 1, m_gridY + 1));
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

void Tile::HandleButtonEvent(SDL_MouseButtonEvent& p_mEv)
{
	if(p_mEv.type==SDL_MOUSEBUTTONDOWN)
	{
		std::cout << "clicked tile " << GetGridPos().x << ' ' << GetGridPos().y << '\n';
		
		m_activeSprite = m_sprites[1];
	}
}





