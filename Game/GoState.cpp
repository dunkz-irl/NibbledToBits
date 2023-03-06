#include "Play.h"
#include "GoState.h"

void GoState::OnEnter()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void GoState::OnExit()
{
	throw std::logic_error("The method or operation is not implemented.");
}

IGameState* GoState::OnUpdate()
{
	return nullptr;
}

void GoState::OnDraw()
{
	throw std::logic_error("The method or operation is not implemented.");
}