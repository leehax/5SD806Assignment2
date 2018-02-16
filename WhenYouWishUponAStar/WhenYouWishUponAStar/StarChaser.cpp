#include "stdafx.h"
#include "StarChaser.h"
#include "ServiceLocator.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "Tile.h"

StarChaser::StarChaser(Tile* p_tile)
{
	m_spriteManager = ServiceLocator<SpriteManager>::GetService();
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	m_spriteWithoutStar = m_spriteManager->CreateSprite("../External/textures/StarChaser.png", 0, 0, 32, 32);
	m_spriteWithStar = m_spriteManager->CreateSprite("../External/textures/StarChaserWithStar.png", 0, 0, 32, 32);
	m_sprite = m_spriteWithoutStar;
	m_curTile = p_tile;
	m_type = "StarChsr";
}


StarChaser::~StarChaser()
{
}

void StarChaser::Update(float p_delta)
{
}

void StarChaser::Draw()
{
	m_drawManager->Draw(m_sprite, GetWorldPos().x, GetWorldPos().y, 1);
}

Vector2<int> StarChaser::GetGridPos()
{
	return m_curTile->GetGridPos();
}

Vector2<int> StarChaser::GetWorldPos()
{
	return m_curTile->GetWorldPos();
}

Tile* StarChaser::GetCurrentTile()
{
	return m_curTile;
}

std::string StarChaser::GetType()
{
	return m_type;
}
