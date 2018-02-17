#include "stdafx.h"
#include "StarChaser.h"
#include "ServiceLocator.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "Tile.h"
#include "World.h"
StarChaser::StarChaser(World& p_world) : m_world(p_world)
{
	m_spriteManager = ServiceLocator<SpriteManager>::GetService();
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	m_spriteWithoutStar = m_spriteManager->CreateSprite("../External/textures/StarChaser.png", 0, 0, 32, 32);
	m_spriteWithStar = m_spriteManager->CreateSprite("../External/textures/StarChaserWithStar.png", 0, 0, 32, 32);
	m_sprite = m_spriteWithoutStar;
	m_type = "StarChsr";
}


StarChaser::~StarChaser()
{
	delete m_sprite;
	m_sprite = nullptr;
	delete m_spriteManager;
	m_spriteManager = nullptr;
	delete m_drawManager;
	m_drawManager = nullptr;
}

void StarChaser::Update(float p_delta)
{

}

void StarChaser::Draw()
{
	m_drawManager->Draw(m_sprite, GetWorldPos().x, GetWorldPos().y, 1);
}

void StarChaser::SetTarget(std::shared_ptr<Tile> p_tile)
{
	m_targetTile = p_tile;
}

