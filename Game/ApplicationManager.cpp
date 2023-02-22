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
