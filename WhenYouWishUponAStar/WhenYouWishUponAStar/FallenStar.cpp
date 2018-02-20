#include "stdafx.h"
#include "FallenStar.h"
#include "ServiceLocator.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "DrawManager.h"

FallenStar::FallenStar()
{
	m_spriteManager = ServiceLocator<SpriteManager>::GetService();
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	m_sprite = m_spriteManager->CreateSprite("../External/textures/Star.png", 0, 0, 32, 32);  
	m_type = "FllnStar";
}


FallenStar::~FallenStar()
{
	delete m_sprite;
	m_sprite = nullptr;
	delete m_spriteManager;
	m_spriteManager = nullptr;
	delete m_drawManager;
	m_drawManager = nullptr;
}

void FallenStar::Update(float p_delta)
{
}

void FallenStar::Draw()
{
	if(m_hidden==false)
		m_drawManager->Draw(m_sprite, GetWorldPos().x, GetWorldPos().y, 1);

}

void FallenStar::Hide(bool p_val)
{
	m_hidden = p_val;
}


