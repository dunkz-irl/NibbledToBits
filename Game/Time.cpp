#include "Play.h"
#include "IGameState.h"
#include "ApplicationManager.h"
#include "Time.h"

float Time::GetStateTime()
{
	m_pCurrentState = nullptr;
	m_pCurrentState = ApplicationManager::Instance().m_pGameState;

	if (m_pCurrentState == nullptr)
	{
		PLAY_ASSERT_MSG(false, "Tried to get state time from invalid GameState")
	}

	return m_pCurrentState->GetStateTime();
}

float Time::GetOverallTime()
{
	if (m_overallTime >= 0.f)
	{
		PLAY_ASSERT_MSG(false, "Overall application time is less than zero!");
	}

	return m_overallTime;
}