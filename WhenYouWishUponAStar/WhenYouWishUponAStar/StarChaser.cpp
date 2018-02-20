#include "stdafx.h"
#include "StarChaser.h"
#include "ServiceLocator.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "Tile.h"
#include "World.h"
#include "FiniteStateMachine.h"
#include <iostream>


void State_Collect::Enter()
{
	//find star
	m_starChaser.SetTargetTile("FllnStar");
	m_starChaser.SetHasStar(false);
}
void State_Sell::Enter()
{
	//find trading post
	m_starChaser.SetTargetTile("TrPost");
	m_starChaser.SetHasStar(true);
	m_energy = 100.f;
}
void State_Rest::Enter()
{
	//find ship
	m_starChaser.SetTargetTile("Ship");
	m_starChaser.SetHasStar(false);
	m_timeToRest = 1.f;
}

void State_Collect::Update(float p_delta)
{
	
	
	//travel to star

	//once traveled to star -> SetState(sell)
	if(m_starChaser.AtTargetTile())
	{
		m_starChaser.SetState("Sell");
	}
	
}

void State_Sell::Update(float p_delta)
{
	

	//travel to trading post
	m_energy -= p_delta*10.f;
	//once traveled to -> SetState(collect)
	if(m_starChaser.AtTargetTile())
	{
		m_starChaser.SetState("Collect");
	}
	//else if fatigued ->SetState(rest)
	if(m_energy<=0.f)
	{
		m_starChaser.SetState("Rest");
	}
}

void State_Rest::Update(float p_delta)
{
	

	//travel to ship
	
	//once traveled to ship -> Rest()
	if(m_starChaser.AtTargetTile())
	{

		m_timeToRest -= p_delta;
		//once rested -> SetState(collect)
		if(m_timeToRest<=0)
		{
			m_starChaser.SetState("Collect");
		}
	}

	
}
void State_Collect::Exit()
{
}
void State_Sell::Exit()
{
}
void State_Rest::Exit()
{
}

StarChaser::StarChaser(World* p_world) : m_world(p_world), m_pathFinding(new AStarPath(p_world))
{
	m_spriteManager = ServiceLocator<SpriteManager>::GetService();
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	m_spriteWithoutStar = m_spriteManager->CreateSprite("../External/textures/StarChaser.png", 0, 0, 32, 32);
	m_spriteWithStar = m_spriteManager->CreateSprite("../External/textures/StarChaserWithStar.png", 0, 0, 32, 32);
	m_sprite = m_spriteWithoutStar;
	m_type = "StarChsr";
	
	AddState("Collect", new State_Collect(*this));
	AddState("Sell", new State_Sell(*this));
	AddState("Rest", new State_Rest(*this));

	
}


StarChaser::~StarChaser()
{
	Destroy();
	delete m_spriteWithStar;
	m_spriteWithStar = nullptr;
	delete m_spriteWithoutStar;
	m_spriteWithoutStar = nullptr;
	delete m_sprite;
	m_sprite = nullptr;

	delete m_spriteManager;
	m_spriteManager = nullptr;

	delete m_drawManager;
	m_drawManager = nullptr;


}

void StarChaser::Update(float p_delta)
{	
	UpdateState(p_delta);
}

void StarChaser::Draw()
{
	m_drawManager->Draw(m_sprite, GetWorldPos().x, GetWorldPos().y, 1);
	
	m_pathFinding->Draw();
}


void StarChaser::SetTargetTile(const std::string p_targetEntitityType)
{
	m_targetTile = m_world->GetTileWithEntity(p_targetEntitityType);
}

bool StarChaser::AtTargetTile()
{
	return m_curTile == m_targetTile;
}

void StarChaser::SetHasStar(bool p_hasStar)
{
	if(p_hasStar)
	{
		m_sprite = m_spriteWithStar;
		m_hasStar = true;
	}
	else
	{
		m_sprite = m_spriteWithoutStar;
		m_hasStar = false;
	}
}

bool StarChaser::HasStar()
{
	return m_hasStar;
}

void StarChaser::RecalculatePath()
{
	m_pathFinding->Recalculate();
	if (m_targetTile) {
		m_path = m_pathFinding->FindPath(GetCurrentTile(), m_targetTile);
	}
}



