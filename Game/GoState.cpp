#include "Play.h"

// States
#include "GoState.h"
#include "PlanningState.h"
#include "PauseState.h"

// Singletons
#include "GameManager.h"
#include "GameObjectManager.h"
#include "GameObject.h"

// Global/helper things
#include "VirtualKeys.h"
#include "Common.h"

void GoState::OnEnter()
{
	GM_INST.m_currentGameState = GAMESTATE_ENUM::GO;
	GameObjectManager::Instance().Create(GameObjectType::TYPE_MOUSE, GameManager::Instance().GetEntrancePosition());
}

void GoState::OnExit()
{
	IGameState::OnExit();
}

IGameState* GoState::OnUpdate()
{
	// Mouse::UpdateAll();

	if (m_proceedToNextState)
	{
		return new PlanningState();
	}

	if (Play::KeyPressed(VK_P))
	{
		return new PauseState();
	}

	GM_INST.UpdateGameObjects();

	return nullptr;
}

void GoState::OnDraw()
{
	throw std::logic_error("The method or operation is not implemented.");
}