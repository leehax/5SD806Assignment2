#pragma once
#include "Config.h"
#include <vector>
class Tile;
class SpriteManager;
class DrawManager;
class Sprite;

class IEntity
{
public:
	IEntity();
	~IEntity();

	virtual void Update(float p_delta)=0;
	virtual void Draw()=0;

	virtual Vector2<int> GetGridPos();
	virtual Vector2<int> GetWorldPos();
	virtual Tile* GetCurrentTile();
	virtual std::string GetType();

protected:
	Tile * m_curTile;
	SpriteManager* m_spriteManager;
	DrawManager* m_drawManager;
	Sprite* m_sprite;

	std::string m_type = "";
};
