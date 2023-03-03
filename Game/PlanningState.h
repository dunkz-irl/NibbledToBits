#pragma once
#include "IGameState.h"

class PlanningState : public IGameState
{

public:
	void OnEnter() override;
	void OnExit() override;
	IGameState* OnUpdate() override;
	void OnDraw() override;
	void ToGoState();

private:
	bool m_proceedToGoState{ false };
};

