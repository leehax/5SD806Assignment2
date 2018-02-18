#pragma once
#include "IGridMap.h"
#include <memory>
#include <vector>
class IEntity;
class GuiButton;
class Spaceship;
class StarChaser;
class FallenStar;
class TradingPost;
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
	std::map<std::pair<int,int>,Tile*> GetTiles();
	bool EntityOnTile(Tile* p_tile);
	Tile* GetTileWithEntity(const std::string p_type);
private:
	unsigned int m_columns, m_rows, m_tileSize;

	std::unique_ptr<Spaceship> m_ship;
	std::unique_ptr<StarChaser> m_starChaser;
	std::unique_ptr<FallenStar> m_fallenStar;
	std::unique_ptr<TradingPost> m_tradingPost;

	std::vector<std::shared_ptr<GuiButton>> m_guiButtons;
	std::shared_ptr<GuiButton> m_selectedGuiButton;
};

