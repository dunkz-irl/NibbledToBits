#pragma once
#include "IGameState.h"

class PlanningState : public IGameState
{

public:
	PlanningState()
	{
		m_debugStateName = "Planning State";
	}

	void OnEnter() override;
	void OnExit() override;
	IGameState* OnUpdate() override;
	void OnDraw() override;
};

