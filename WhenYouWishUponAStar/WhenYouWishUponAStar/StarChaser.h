#pragma once
#include "IEntity.h"
#include <memory>
#include "IState.h"

class State_Collect:public IState
{
	void Update(float p_delta) override;
};
class State_Sell:public IState
{
	void Update(float p_delta) override;
};
class State_Rest:public IState
{
	void Update(float p_delta) override;
	
};
class FallenStar;
class World;
class FiniteStateMachine;
class StarChaser :public IEntity
{
public:
	StarChaser(World& p_world);
	~StarChaser();
	void Update(float p_delta) override;
	void Draw() override;
	void SetTarget(std::shared_ptr<Tile> p_tile);

private:
	std::shared_ptr<Tile> m_targetTile;
	World& m_world;
	Sprite* m_spriteWithStar;
	Sprite* m_spriteWithoutStar;
	FiniteStateMachine& m_FSM;
};

