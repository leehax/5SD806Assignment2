#include "stdafx.h"
#include "TradingPost.h"
#include "Tile.h"

TradingPost::TradingPost()
{
}


TradingPost::~TradingPost()
{
}

void TradingPost::Update(float p_delta)
{
}

void TradingPost::Draw()
{
}

Vector2<int> TradingPost::GetGridPos()
{
	return m_curTile->GetGridPos();
}

Vector2<int> TradingPost::GetWorldPos()
{
	return m_curTile->GetWorldPos();
}

Tile* TradingPost::GetCurrentTile()
{
	return m_curTile;
}

std::string TradingPost::GetType()
{
	return m_type;
}
