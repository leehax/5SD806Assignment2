#pragma once
#include <vector>
#include "Sprite.h"
#include "Config.h"



class GridMap;
class DrawManager;
class SpriteManager;
class Tile 
{
public:
	Tile(int p_x,  int p_y,  int p_w,  int p_h, int p_gridX, int p_gridY);
	~Tile();
	SDL_Rect* GetRect();
	void Draw(Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a);
	void Update(float p_delta);
	void FindNeighbours();
	std::vector<Tile*> GetNeighbours();
	Vector2<int> GetWorldPos();
	Vector2<int> GetGridPos();
	GridMap* m_gridMap;


	void Lock(int p_ID, std::string p_type);
	void Unlock(int p_ID, std::string p_type);
	bool Locked(int p_ID, std::string p_type);
private:

	SDL_Rect m_rect;
	DrawManager* m_drawManager;
	SpriteManager* m_spriteManager;

	Sprite* m_sprite;
	std::vector<Tile*> m_neighbours;
	int m_gridX, m_gridY;
	int m_x, m_y;
	int m_lockedByID; 
	std::string m_lockedByType;
};

