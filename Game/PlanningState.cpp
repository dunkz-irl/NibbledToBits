#include "Play.h"
 
#include "PlanningState.h"
#include "GoState.h"
#include "PauseState.h"

#include "GameManager.h"

#include "VirtualKeys.h"

void PlanningState::OnEnter()
{
	GM_INST.m_currentGameState = GAMESTATE_ENUM::PLANNING;
}

void PlanningState::OnExit()
{
	IGameState::OnExit();
}

IGameState* PlanningState::OnUpdate()
{
	if (m_proceedToNextState)
	{
		return new GoState();
	}

	if (Play::KeyPressed(VK_P))
	{
		return new PauseState();
	}

	return nullptr;
}

void PlanningState::OnDraw()
{
	GM_INST.DrawHeldItem();
	GM_INST.DrawStartButton();

	// throw std::logic_error("The method or operation is not implemented.");
}