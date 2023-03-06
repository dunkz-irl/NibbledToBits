#pragma once
#include "IGameState.h"

class PauseState : public IGameState
{

public:
	PauseState();

	void OnEnter() override;
	void OnExit() override;
	IGameState* OnUpdate() override;
	void OnDraw() override;

	friend class GameManager;

private:
	IGameState* m_previousState;
};

