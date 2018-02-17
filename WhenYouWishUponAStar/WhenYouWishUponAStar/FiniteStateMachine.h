#pragma once
#include "IState.h"
class FiniteStateMachine
{
public:
	FiniteStateMachine();
	~FiniteStateMachine();
	void SetState(IState* p_state);
	void Update(float p_delta);
private:

	IState* m_activeState;
};

