#include "Play.h"

#include "GameManager.h"
#include "Common.h"
#include "Mouse.h"

#include "EmptySquare.h"

void EmptySquare::OnCurrentSquare(void* pObj)
{
	Mouse* pMouse = static_cast<Mouse*>(pObj);
	
	// Don't go beyond bounds of grid, except when the exit
	GridVector nextPos = pMouse->GetNextPosition();

	if (nextPos.x == -1 || nextPos.x == GRID_WIDTH || nextPos.y == -1 || nextPos.y == GRID_HEIGHT - 1)
	{
		GameAreaObject* pExit = GM_INST.GetExitObj();
		if (nextPos == GridVector{pExit->posx, pExit->posy})
		{
			return;
		}

		pMouse->ReverseDirection();
		pMouse->UpdateTrackedGridSquares();
	}
}