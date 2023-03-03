#pragma once
#include "IGameState.h"

class GoState : public IGameState
{

public:
	void OnEnter() override;
	void OnExit() override;
	IGameState* OnUpdate() override;
	void OnDraw() override;

};

