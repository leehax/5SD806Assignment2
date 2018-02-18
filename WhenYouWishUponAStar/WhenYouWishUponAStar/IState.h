#pragma once
class IState
{
public:
	virtual ~IState() = default;
	virtual void Enter() = 0;
	virtual void Update(float p_delta) = 0;
	virtual void Exit() = 0;

};

