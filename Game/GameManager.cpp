#include "Play.h"
#include "Common.h"

#include "MenuState.h"
#include "GameArea.h"

#include "PanelItem.h"
#include "Panel.h"
#include "GoButton.h"

#include "PlanningState.h"

#include "GameManager.h"
#include "LoadLevel.h"

GameManager* GameManager::s_pInstance = nullptr;
//extern std::map<std::string, int> g_idMap;

GameManager::GameManager()
{
	s_pInstance = this;

	m_gameArea = new GameArea;
	m_currentHeld = new FloatingObject;

	// Initialise Start Button
	m_goButton = new GoButton(Play::GetSpriteId("tick_panel"), {DISPLAY_WIDTH * 0.875f, DISPLAY_HEIGHT * 0.1f}, Play::Vector2f{ 100, 100 });

	m_pGameState = new PlanningState();
	m_pGameState->OnEnter();
}

GameManager::~GameManager()
{
	delete m_currentHeld;
	delete m_gameArea;
	s_pInstance = nullptr;
}

GameManager& GameManager::Instance()
{
	if (!s_pInstance)
	{
		s_pInstance = new GameManager;
	}

	return *s_pInstance;
}

void GameManager::Destroy()
{
	delete s_pInstance;
}

void GameManager::Update()
{
	UpdateStartButton(); // #TODO: Move this somewhere more sensible

	// Call OnUpdate of current state, which returns either a new state or nullptr
	IGameState* pNewState = m_pGameState->OnUpdate();

	if (pNewState != nullptr)
	{
		m_pGameState->OnExit();
		delete m_pGameState;
		m_pGameState = pNewState;
		m_pGameState->OnEnter();
	}
}

void GameManager::LoadLevel(const char* levelName)
{
	LevelLoader loader;
	loader.LoadLevel(levelName);
}

GridPoint GameManager::GetEntrancePosition()
{
	if (!(m_gameArea->m_holeEntry.posx < -1) && !(m_gameArea->m_holeEntry.posy < -1))
	{
		return { m_gameArea->m_holeEntry.posx, m_gameArea->m_holeEntry.posy };
	}
	else
	{
		PLAY_ASSERT_MSG(false, "Entrance position is invalid.")
		return { -2, -2 };
	}
}

GridPoint GameManager::GetExitPosition()
{
	if (!(m_gameArea->m_holeExit.posx < -1) && !(m_gameArea->m_holeExit.posy < -1))
	{
		return { m_gameArea->m_holeExit.posx, m_gameArea->m_holeExit.posy };
	}
	else
	{
		PLAY_ASSERT_MSG(false, "Exit position is invalid.")
		return { -2, -2 };
	}
}

void GameManager::ManageInput()
{
	// #CREDIT Fagin and Abdullah
	// handle grabbing
	if (Play::KeyPressed(VK_LBUTTON))
	{
		delete m_currentHeld;
		m_currentHeld = new FloatingObject{ m_panel->GetSelection(), 0, 0 };
		if (m_currentHeld->id == -1)
		{
			delete m_currentHeld;
			m_currentHeld = new FloatingObject(m_gameArea->GetObject());
		}
	}

	//Handle placing
	if (!Play::KeyDown(VK_LBUTTON))
	{
		if (m_currentHeld->id >= 0)
		{
			m_gameArea->PlaceObject(*m_currentHeld);
		}

		delete m_currentHeld;
		m_currentHeld = new FloatingObject{ -1, 0, 0 };
	}
}

void GameManager::DrawHeldItem()
{
	// #CREDIT Fagin and Abdullah
	// draw held item
	if (m_currentHeld->mouseHole) {
		Play::Point2D mousePos = Play::GetMousePos();

		Play::DrawSprite(m_gameArea->mouseHoleSpriteIDs[0], mousePos, 0);
	}
	else {
		if (m_currentHeld->id >= 0)
		{
			Play::Point2D mousePos = Play::GetMousePos();

			int spriteID = GetSpriteIDFromObjectID(m_currentHeld->id, m_currentHeld->rot);

			PLAY_ASSERT_MSG(spriteID != -1, "invalid sprite id");
			Play::DrawSprite(spriteID, mousePos, 0);
		}
	}
}

void GameManager::DrawStartButton()
{
	// Little background
	Play::SetDrawingBlendMode(BLEND_SUBTRACT);
	Play::DrawSpriteRotated("tick_panel_blurred", m_goButton->GetPosition() + Vector2D{m_goButton->GetSize().x / 2.f, m_goButton->GetSize().y / 2.f}, 0, 0, 1.f, 0.5f);
	Play::SetDrawingBlendMode(BLEND_NORMAL);
	m_goButton->Draw();
}

void GameManager::SetGameState(IGameState* state)
{
	if (state)
	{
		m_pGameState = state;
	}
	else
	{
		PLAY_ASSERT_MSG(false, "Tried to set GameManager's GameState to nullptr");
	}
}

void GameManager::UpdateStartButton()
{
	m_goButton->Update(); // Currently doesn't do anything
}

GameObject* GameManager::GetGameObject(int id)
{
	//for (GameObject* : m_vGameObjectIDs)
	//{

	//}

	return nullptr;
}