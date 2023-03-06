#pragma once
#include "IGameState.h"

class GoState : public IGameState
{

public:
	GoState()
	{
		m_debugStateName = "Go State";
	}

	void OnEnter() override;
	void OnExit() override;
	IGameState* OnUpdate() override;
	void OnDraw() override;
};

