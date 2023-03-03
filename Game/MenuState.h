#pragma once
#include "IApplicationState.h"

class SimpleGraphic;

class MenuState : public IApplicationState
{

public:
	void OnEnter();
	void OnExit();
	IApplicationState* OnUpdate();
	void OnDraw();

private:
	int m_testCounter{ 0 };
	std::vector<SimpleGraphic*> m_vSimpleGraphics;

};
