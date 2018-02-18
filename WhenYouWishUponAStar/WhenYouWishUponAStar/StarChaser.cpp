#include "stdafx.h"
#include "StarChaser.h"
#include "ServiceLocator.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "Tile.h"
#include "World.h"
#include "FiniteStateMachine.h"
#include <iostream>


//void ChaserState::Draw()
//{
//	m_pathFinding->Draw();
//}
//
//void State_Collect::Enter()
//{
//	m_targetTile = m_world.GetTileWithEntity("FllnStar");
//	m_pathFinding->FindPath(m_starChaser.GetCurrentTile(), m_targetTile);
//}
//void State_Sell::Enter()
//{
//	m_targetTile = m_world.GetTileWithEntity("TrPost");
//	m_energy = 100.f;
//}
//void State_Rest::Enter()
//{
//	m_targetTile = m_world.GetTileWithEntity("Ship");
//}
//
//void State_Collect::Update(float p_delta)
//{
//	//find star
//	
//	//travel to star
//
//	//once traveled to star -> SetState(sell)
//}
//
//void State_Sell::Update(float p_delta)
//{
//	//find trading post
//
//	//travel to trading post
//	m_energy -= p_delta*10.f;
//	//once traveled to -> SetState(collect)
//	//else if fatigued ->SetState(rest)
//	if(m_energy<=0.f)
//	{
//		m_starChaser.SetState("Rest");
//	}
//}
//
//void State_Rest::Update(float p_delta)
//{
//	//find ship
//
//	//travel to ship
//	
//	//once traveled to ship -> Rest()
//
//	//once rested -> SetState(collect)
//}
//void State_Collect::Exit()
//{
//}
//void State_Sell::Exit()
//{
//}
//void State_Rest::Exit()
//{
//}

StarChaser::StarChaser(World* p_world) : m_world(p_world), m_pathFinding(new AStarPath(p_world))
{
	m_spriteManager = ServiceLocator<SpriteManager>::GetService();
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	m_spriteWithoutStar = m_spriteManager->CreateSprite("../External/textures/StarChaser.png", 0, 0, 32, 32);
	m_spriteWithStar = m_spriteManager->CreateSprite("../External/textures/StarChaserWithStar.png", 0, 0, 32, 32);
	m_sprite = m_spriteWithoutStar;
	m_type = "StarChsr";
	
	/*AddState("Collect", new State_Collect(*this,m_world));
	AddState("Sell", new State_Sell(*this, m_world));
	AddState("Rest", new State_Rest(*this, m_world));*/

	
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
	
	//UpdateState(p_delta);
}

void StarChaser::Draw()
{
	m_drawManager->Draw(m_sprite, GetWorldPos().x, GetWorldPos().y, 1);
	m_pathFinding->Draw();
}

void StarChaser::FindPath()
{
	m_targetTile = m_world->GetTileWithEntity("FllnStar");
	m_pathFinding->FindPath(GetCurrentTile(), m_targetTile);
}

void StarChaser::ClearPath()
{
	m_pathFinding->Clear();
}



