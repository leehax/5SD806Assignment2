#pragma once
#include "IEntity.h"
class Spaceship :
	public IEntity
{
public:
	Spaceship(Tile* p_tile);
	~Spaceship();
	void Update(float p_delta) override;
	void Draw() override;

};

