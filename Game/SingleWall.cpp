#include "Play.h"
#include "Common.h"

#include "SingleWall.h"
#include "Mouse.h"

void SingleWall::OnCurrentSquare(void* pObj)
{
	if (active || vis)
	{
		throw std::logic_error("This should never happen.");
	}
}

void SingleWall::OnNextSquare(void* pObj)
{
	if (active)
	{
		Mouse* pMouse = static_cast<Mouse*>(pObj);

		pMouse->ReverseDirection();
		pMouse->UpdateTrackedGridSquares();
	}
}

void SingleWall::Reset()
{
	vis = true;
	active = true;
}