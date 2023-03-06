#include "Play.h"

#include "IGameState.h"
#include "IApplicationState.h"
#include "GameManager.h"
#include "ApplicationManager.h"
#include "Time.h"

float Time::GetAppStateTime() // #TODO: Could be confused with GameState Time - separate?
{
	m_pCurrentAppState = nullptr;
	m_pCurrentAppState = ApplicationManager::Instance().m_pApplicationState;

	if (m_pCurrentAppState == nullptr)
	{
		PLAY_ASSERT_MSG(false, "Tried to get state time from invalid ApplicationState")
	}

	return m_pCurrentAppState->GetStateTime();
}

float Time::GetOverallTime()
{
	if (m_overallTime <= 0.f)
	{
		PLAY_ASSERT_MSG(false, "Overall application time is less than zero!");
	}

	return m_overallTime;
}

float Time::GetGameStateTime()
{
	m_pCurrentGameState = nullptr;
	m_pCurrentGameState = GM_INST.m_pGameState;

	if (m_pCurrentGameState == nullptr)
	{
		PLAY_ASSERT_MSG(false, "Tried to get state time from invalid GameState");
	}

	return m_pCurrentGameState->GetStateTime();
}

float Time::GetElapsedTime()
{
	if (m_elapsedTime < 0.f)
	{
		PLAY_ASSERT_MSG(false, "Something bad has happened - elapsed time is less than zero")
	}

	return m_elapsedTime;
}
