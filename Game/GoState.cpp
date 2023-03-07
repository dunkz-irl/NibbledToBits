#include "Play.h"

// States
#include "GoState.h"
#include "PlanningState.h"
#include "PauseState.h"

// Singletons
#include "GameManager.h"
#include "GameObjectManager.h"
#include "GameObject.h"

// Other
#include "MouseSpawner.h"

// Global/helper things
#include "VirtualKeys.h"
#include "Common.h"

GoState::GoState()
{
	m_debugStateName = "Go State";
	std::pair<int, float> mouseInfo = GM_INST.GetMouseSpawnInfo();
	m_mouseSpawner = new MouseSpawner(mouseInfo.first, mouseInfo.second);
}

void GoState::OnEnter()
{
	GM_INST.m_currentGameState = GAMESTATE_ENUM::GO;
}

void GoState::OnExit()
{
	IGameState::OnExit();
	delete m_mouseSpawner;
}

IGameState* GoState::OnUpdate()
{
	if(m_mouseSpawner->Update())
	{
		GameObjectManager::Instance().Create(GameObjectType::TYPE_MOUSE, GameManager::Instance().GetEntrancePosition());
	}

	if (m_proceedToNextState)
	{
		return new PlanningState();
	}

	if (Play::KeyPressed(VK_P))
	{
		return new PauseState();
	}

	return nullptr;
}

void GoState::OnDraw()
{
	throw std::logic_error("The method or operation is not implemented.");
}