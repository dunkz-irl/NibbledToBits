#include "Play.h"
#include "PlanningState.h"
#include "GoState.h"

void PlanningState::OnEnter()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void PlanningState::OnExit()
{
	throw std::logic_error("The method or operation is not implemented.");
}

IGameState* PlanningState::OnUpdate()
{
	if (m_proceedToNextState)
	{
		return new GoState();
	}

	return nullptr;
}

void PlanningState::OnDraw()
{
	throw std::logic_error("The method or operation is not implemented.");
}