#pragma once
#include "IGameState.h"

extern std::map<std::string, int> g_idMap;
class Button;

class WinState : public IGameState
{
	// Inherited via IGameState
	virtual void OnEnter() override;
	virtual IGameState* OnUpdate() override;
	virtual void OnDraw() override;
	virtual void OnExit() override;

private:
	Button* m_continueButton;
	Play::Point2f m_continueButtonPos;
};

