#include "Play.h"
#include "Time.h"
#include "Common.h"
#include "MenuState.h"
#include "ApplicationManager.h"

ApplicationManager* ApplicationManager::s_pInstance = nullptr;

ApplicationManager::ApplicationManager()
{
	s_pInstance = this;

	m_pGameState = new MenuState();
	m_pGameState->OnEnter();
}

ApplicationManager::~ApplicationManager()
{
	s_pInstance = nullptr;
}

ApplicationManager& ApplicationManager::Instance()
{
	if (!s_pInstance)
	{
		s_pInstance = new ApplicationManager;
	}

	return *s_pInstance;
}

void ApplicationManager::Destroy()
{
	
}

void ApplicationManager::Update(float elapsedTime)
{
	m_pGameState->m_stateTime += elapsedTime;
	Time::m_overallTime += elapsedTime;

	// Call OnUpdate of current state, which returns either a new state or nullptr
	IApplicationState* pNewState = m_pGameState->OnUpdate();

	if (pNewState != nullptr)
	{
		m_pGameState->OnExit();
		delete m_pGameState;
		m_pGameState = pNewState;
		m_pGameState->m_stateTime = 0.f;
		m_pGameState->OnEnter();
	}
}

void ApplicationManager::Draw()
{
	m_pGameState->OnDraw();

	if (m_DebugMode)
	{
		// Couldn't get this to work with the rectangle being filled in
		//Play::DrawRect({ DISPLAY_WIDTH * 0.01f, DISPLAY_HEIGHT * 0.06f }, { DISPLAY_WIDTH * 0.2f, DISPLAY_HEIGHT * 0.01f }, Play::cGrey, false);

		Play::DrawDebugText({ DISPLAY_WIDTH * 0.025f, DISPLAY_HEIGHT * 0.05f }, "Overall Time:", Play::cRed, false);
		Play::DrawDebugText({ DISPLAY_WIDTH * 0.135f, DISPLAY_HEIGHT * 0.05f }, DEBUG_TEXT(Time::m_overallTime), Play::cRed, false);

		Play::DrawDebugText({ DISPLAY_WIDTH * 0.025f, DISPLAY_HEIGHT * 0.1f }, "State Time:", Play::cRed, false);
		Play::DrawDebugText({ DISPLAY_WIDTH * 0.135f, DISPLAY_HEIGHT * 0.1f }, DEBUG_TEXT(m_pGameState->m_stateTime), Play::cRed, false);
	}
}
