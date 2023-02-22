#pragma once
#include "IGameState.h"

class PlayState : public IGameState
{
public:
	void OnEnter();
	void OnExit();

	IGameState* OnUpdate();
	void OnDraw();

};
