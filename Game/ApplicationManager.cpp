#include "MenuState.h"
#include "ApplicationManager.h"

ApplicationManager::ApplicationManager()
{
	m_pGameState = new MenuState();
	m_pGameState->OnEnter();
}

ApplicationManager::~ApplicationManager()
{

}

void ApplicationManager::Update()
{
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

void ApplicationManager::Draw()
{
	m_pGameState->OnDraw();
}
