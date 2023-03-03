#pragma once
#include "IApplicationState.h"

class MainGameState : public IApplicationState
{
public:
	void OnEnter();
	void OnExit();

	IApplicationState* OnUpdate();
	void OnDraw();

};
