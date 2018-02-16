#pragma once
#include "IGridMap.h"
#include <memory>
#include <vector>
class IEntity;
class GuiButton;
class Spaceship;
class StarChaser;

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
	std::vector<Tile*> GetTiles();
private:
	unsigned int m_columns, m_rows, m_tileSize;
	std::shared_ptr<Spaceship> m_ship;
	std::shared_ptr<StarChaser> m_starchsr;
	std::vector<std::shared_ptr<IEntity>> m_entities;
	std::vector<std::shared_ptr<GuiButton>> m_guiButtons;
	std::shared_ptr<GuiButton> m_activeSpawnButton;
};

