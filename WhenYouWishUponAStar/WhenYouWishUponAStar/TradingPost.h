#pragma once
#include "IEntity.h"
class TradingPost :
	public IEntity
{
public:
	TradingPost();
	~TradingPost();
	void Update(float p_delta) override;
	void Draw() override;

	Vector2<int> GetGridPos() override;
	Vector2<int> GetWorldPos() override;
	Tile* GetCurrentTile()override;
	std::string GetType()override;
};

