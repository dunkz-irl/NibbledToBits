#include "Play.h"

#include "Common.h"
#include "PauseState.h"
#include "VirtualKeys.h"

#include "GameManager.h"

PauseState::PauseState()
{
	m_debugStateName = "Pause State";
}

void PauseState::OnEnter()
{
	GM_INST.m_currentGameState = GAMESTATE_ENUM::PAUSE;
	// throw std::logic_error("The method or operation is not implemented.");
}

void PauseState::OnExit()
{
	IGameState::OnExit();
	// throw std::logic_error("The method or operation is not implemented.");
}

IGameState* PauseState::OnUpdate()
{
	if (Play::KeyPressed(VK_P))
	{

	}
	return nullptr;
}

void PauseState::OnDraw()
{
	Play::DrawRect({ DISPLAY_WIDTH * 0.15f, DISPLAY_HEIGHT * 0.15f }, { DISPLAY_WIDTH * 0.85f, DISPLAY_HEIGHT * 0.85f }, Play::cGrey, true);
	Play::DrawFontText("ABNORMAL40px_10x10", "PAUSE MENU", CENTRE_POINT, Play::CENTRE);

	// throw std::logic_error("The method or operation is not implemented.");
}
