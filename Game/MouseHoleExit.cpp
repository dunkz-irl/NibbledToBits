#include "Play.h"
#include "Common.h"

#include "MouseHoleExit.h"
#include "Mouse.h"
#include "GoState.h"

#include "ParticleManager.h"

void MouseHoleExit::OnCurrentSquare(void* pObj)
{
	Mouse* pMouse = static_cast<Mouse*>(pObj);
	pMouse->SetType(GameObjectType::TYPE_CLEANUP);

	// #TODO: Add particle effect

	Play::Point2f worldPos = GameArea::GameToWorld(Play::Point2f(posx, posy));
	ParticleManager::Instance().CreateEmitter(EmitterType::CHEESE, worldPos, 0.1f);

	GoState::IncrementSavedMice();
}
