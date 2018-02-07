#pragma once
#include <vector>
#include "Sprite.h"
#include "Config.h"



class World;
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
	void HandleButtonEvent(SDL_MouseButtonEvent& p_mEv);
	World* m_world;


private:

	SDL_Rect m_rect;
	DrawManager* m_drawManager;
	SpriteManager* m_spriteManager;
	Sprite* m_activeSprite;
	std::vector<Sprite*> m_sprites;
	std::vector<Tile*> m_neighbours;
	unsigned int m_gridX, m_gridY, m_x, m_y;;


};

