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
		pMouse->ReverseDirection();
		pMouse->UpdateTrackedGridSquares();
	}
}
