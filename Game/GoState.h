#pragma once
#include "IGameState.h"

class MouseSpawner;

class GoState : public IGameState
{

public:
	GoState();

	void OnEnter() override;
	void OnExit() override;
	IGameState* OnUpdate() override;
	void OnDraw() override;

	static void IncrementSavedMice();

private:
	MouseSpawner* m_mouseSpawner;
};

