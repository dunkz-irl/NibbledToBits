#include "Play.h"
#include "Common.h"

#include "SingleWall.h"
#include "Mouse.h"

void SingleWall::OnCurrentSquare(void* pObj)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void SingleWall::OnNextSquare(void* pObj)
{
	Mouse* pMouse = static_cast<Mouse*>(pObj);

	pMouse->ReverseDirection();
	pMouse->UpdateTrackedGridSquares();
}
