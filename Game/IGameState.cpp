#include "Play.h"
#include "Time.h"
#include "Common.h"
#include "IGameState.h"

void IGameState::OnExit()
{
	m_stateTime = { 0.f };
}

void IGameState::DrawDebugInfo()
{
	Play::DrawDebugText({ DISPLAY_WIDTH * 0.025f, DISPLAY_HEIGHT * 0.3f }, "Game State:", Play::cRed, false);
	Play::DrawDebugText({ DISPLAY_WIDTH * 0.135f, DISPLAY_HEIGHT * 0.3f }, m_debugStateName.c_str(), Play::cRed, false);

	Play::DrawDebugText({ DISPLAY_WIDTH * 0.025f, DISPLAY_HEIGHT * 0.25f }, "Game State Time:", Play::cRed, false);
	Play::DrawDebugText({ DISPLAY_WIDTH * 0.135f, DISPLAY_HEIGHT * 0.25f }, DEBUG_TEXT(Time::GetGameStateTime()), Play::cRed, false);	
}
