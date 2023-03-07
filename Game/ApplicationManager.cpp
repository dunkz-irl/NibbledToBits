#include "Play.h"
#include "Time.h"
#include "Common.h"
#include "MainGameState.h"
#include "ApplicationManager.h"
#include "GameManager.h"
#include "Debug.h"

ApplicationManager* ApplicationManager::s_pInstance = nullptr;

ApplicationManager::ApplicationManager()
{
	s_pInstance = this;

	m_pApplicationState = new MainGameState(); // #TODO: Change to MenuState when finished
	m_pApplicationState->OnEnter();
}

ApplicationManager::~ApplicationManager()
{
	GM_INST.Destroy();

	delete m_pApplicationState;
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
	delete s_pInstance;
}

void ApplicationManager::Update(float elapsedTime)
{
	m_pApplicationState->m_stateTime += elapsedTime;
	Time::m_overallTime += elapsedTime;
	Time::m_elapsedTime = elapsedTime;

	// Call OnUpdate of current state, which returns either a new state or nullptr
	IApplicationState* pNewState = m_pApplicationState->OnUpdate();

	if (pNewState != nullptr)
	{
		m_pApplicationState->OnExit();
		delete m_pApplicationState;
		m_pApplicationState = pNewState;
		m_pApplicationState->m_stateTime = 0.f;
		m_pApplicationState->OnEnter();
	}

	if (Play::KeyPressed(VK_HOME))
	{
		Debug::s_active = !Debug::s_active;
	}
}

void ApplicationManager::Draw()
{
	m_pApplicationState->OnDraw();

	if (Debug::s_active)
	{
		m_pApplicationState->DrawDebugInfo();
	}
}
