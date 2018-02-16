#pragma once
#include "IEntity.h"
#include <memory>

class StarChaser :public IEntity
{
public:
	StarChaser(Tile* p_tile);
	~StarChaser();
	void Update(float p_delta) override;
	void Draw() override;

	Vector2<int> GetGridPos() override;
	Vector2<int> GetWorldPos() override;
	Tile* GetCurrentTile()override;
	std::string GetType()override;
private:
	Sprite* m_spriteWithStar;
	Sprite* m_spriteWithoutStar;
};

