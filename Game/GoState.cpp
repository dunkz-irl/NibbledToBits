#include "Play.h"

// States
#include "GoState.h"
#include "PlanningState.h"
#include "PauseState.h"
#include "WinState.h"

// Singletons
#include "GameManager.h"
#include "GameObjectManager.h"

#include "Common.h"
#include "GameObject.h"

// Other
#include "MouseSpawner.h"
#include "GameArea.h"

// Global/helper things
#include "VirtualKeys.h"
#include "Common.h"

GoState::GoState()
{
	m_debugStateName = "Go State";
	m_thisState = GAMESTATE_ENUM::GO;
	GM_INST.m_currentGameState = GAMESTATE_ENUM::GO;
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

	GameObjectManager::Instance().CleanupAllOfType(GameObjectType::TYPE_MOUSE);
	GameObjectManager::Instance().CleanupAllOfType(GameObjectType::TYPE_DESTROYED);

	// Reset all game area objects
	for (int x = 0; x < GRID_WIDTH; x++)
	{
		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			GameArea::m_gameAreaObjects[x][y]->Reset();
		}
	}

	GM_INST.ResetLevel();

	delete m_mouseSpawner;
}

IGameState* GoState::OnUpdate()
{
	if(m_mouseSpawner->Update())
	{
		GameObjectManager::Instance().Create(GameObjectType::TYPE_MOUSE, GameManager::Instance().GetEntrancePosition());
	}

	// Update GameAreaObjects
	for (int x = 0; x < GRID_WIDTH; x++)
	{
		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			GameArea::m_gameAreaObjects[x][y]->Update();
		}
	}

	if (m_proceedToNextState)
	{
		return new PlanningState();
	}

	if (Play::KeyPressed(VK_P))
	{
		return new PauseState();
	}

	if (GM_INST.m_savedMice == GM_INST.m_targetSavedMice)
	{
		GameObjectManager::Instance().CleanupAllOfType(GameObjectType::TYPE_CLEANUP);
		return new WinState();
	}

	GameObjectManager::Instance().CleanupAllOfType(GameObjectType::TYPE_CLEANUP);

	return nullptr;
}

void GoState::OnDraw()
{
	GM_INST.DrawHeldItem();
	GM_INST.DrawStartButton();
	GM_INST.DrawUI();
	// throw std::logic_error("The method or operation is not implemented.");

	// Draw GameAreaObjects (most are done somewhere else, but tank has this method)
	for (int x = 0; x < GRID_WIDTH; x++)
	{
		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			GameArea::m_gameAreaObjects[x][y]->Draw();
		}
	}
}

void GoState::IncrementSavedMice()
{
	// #TODO: This might be weird if the current state wasn't a GoState, but it should be hopefully??
	GoState* pInstanceGoState = static_cast<GoState*>(GM_INST.m_pGameState);

	if (!(GM_INST.m_savedMice > GM_INST.m_targetSavedMice))
	{
		GM_INST.m_savedMice++;
	}
	else
	{
		PLAY_ASSERT_MSG(false, "Tried to increment saved mice past maximum");
	}
}
