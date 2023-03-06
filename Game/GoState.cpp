#include "Play.h"

#include "GoState.h"
#include "PlanningState.h"
#include "PauseState.h"

#include "GameManager.h"
#include "VirtualKeys.h"

void GoState::OnEnter()
{
	GM_INST.m_currentGameState = GAMESTATE_ENUM::GO;
	throw std::logic_error("The method or operation is not implemented.");
}

void GoState::OnExit()
{
	IGameState::OnExit();
	throw std::logic_error("The method or operation is not implemented.");
}

IGameState* GoState::OnUpdate()
{
	if (m_proceedToNextState)
	{
		return new PlanningState();
	}

	if (Play::KeyPressed(VK_P))
	{
		return new PauseState();
	}

	return nullptr;
}

void GoState::OnDraw()
{
	throw std::logic_error("The method or operation is not implemented.");
}