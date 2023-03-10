#include "Play.h"
#include "Common.h"

#include "MouseHoleExit.h"
#include "Mouse.h"
#include "GoState.h"

void MouseHoleExit::OnCurrentSquare(void* pObj)
{
	Mouse* pMouse = static_cast<Mouse*>(pObj);
	pMouse->SetType(GameObjectType::TYPE_CLEANUP);

	// #TODO: Add particle effect

	GoState::IncrementSavedMice();
}
