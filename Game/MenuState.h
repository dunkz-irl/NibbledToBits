#pragma once
#include "IGameState.h"

class SimpleGraphic;

class MenuState : public IGameState
{

public:
	void OnEnter();
	void OnExit();
	IGameState* OnUpdate();
	void OnDraw();

private:
	int m_testCounter{ 0 };
	std::vector<SimpleGraphic*> m_vSimpleGraphics;

};
