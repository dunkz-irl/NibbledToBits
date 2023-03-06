#include "Play.h"
 
#include "PlanningState.h"
#include "GoState.h"
#include "PauseState.h"

#include "GameManager.h"

#include "VirtualKeys.h"

void PlanningState::OnEnter()
{
	GM_INST.m_currentGameState = GAMESTATE_ENUM::PLANNING;
	throw std::logic_error("The method or operation is not implemented.");
}

void PlanningState::OnExit()
{
	IGameState::OnExit();
	throw std::logic_error("The method or operation is not implemented.");
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
	throw std::logic_error("The method or operation is not implemented.");
}