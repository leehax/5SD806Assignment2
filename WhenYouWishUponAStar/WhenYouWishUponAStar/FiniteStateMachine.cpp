#include "stdafx.h"
#include "FiniteStateMachine.h"


FiniteStateMachine::FiniteStateMachine()
{
}


FiniteStateMachine::~FiniteStateMachine()
{
}

void FiniteStateMachine::SetState(IState* p_state)
{
	m_activeState = p_state;
}

void FiniteStateMachine::Update(float p_delta)
{
	m_activeState->Update(p_delta);
}

