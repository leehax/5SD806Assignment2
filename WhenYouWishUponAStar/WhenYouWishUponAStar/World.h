#pragma once
#include "IGridMap.h"
class World :
	public IGridMap
{
public:
	World();
	~World();
	void Initialise() override;
	void DrawGrid(Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a) override;
	void Update(float p_delta) override;
	Tile* GetTile(int p_gridX, int p_gridY) override;
	void HandleEvent(SDL_Event& p_ev, SDL_Point p_pos) override;
private:
	unsigned int m_columns, m_rows, m_tileSize;

};

