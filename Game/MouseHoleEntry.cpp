#include "Play.h"
#include "Common.h"

#include "Mouse.h"
#include "MouseHoleEntry.h"

void MouseHoleEntry::OnCurrentSquare(void* pMouse)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void MouseHoleEntry::OnNextSquare(void* pObj)
{
	Mouse* pMouse = static_cast<Mouse*>(pObj);

	if (pMouse->GetNextPosition().x == posx && pMouse->GetNextPosition().y == posy)
	{
		GridVector holeToMouse = GridVector{posx, posy} - pMouse->GetGridPosition();
		pMouse->ForcePosition(GridVector{posx + holeToMouse.x, posy + holeToMouse.y}, GridVector{ posx + holeToMouse.x * 2, posy + holeToMouse.y * 2 });
		pMouse->UpdateTrackedGridSquares();
	}
}
