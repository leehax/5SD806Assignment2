#pragma once
#include "IEntity.h"

class FallenStar:public IEntity
{
public:
	FallenStar();
	~FallenStar();

	void Update(float p_delta) override;
	void Draw() override;


};

