#include "Play.h"
#include "Common.h"
#include "Time.h"

#include "IApplicationState.h"

void IApplicationState::DrawDebugInfo()
{
	Play::DrawDebugText({ DISPLAY_WIDTH * 0.025f, DISPLAY_HEIGHT * 0.15f }, "App State:", Play::cRed, false);
	Play::DrawDebugText({ DISPLAY_WIDTH * 0.135f, DISPLAY_HEIGHT * 0.15f }, m_debugStateName.c_str(), Play::cRed, false);

	// Couldn't get this to work with the rectangle being filled in
	//Play::DrawRect({ DISPLAY_WIDTH * 0.01f, DISPLAY_HEIGHT * 0.06f }, { DISPLAY_WIDTH * 0.2f, DISPLAY_HEIGHT * 0.01f }, Play::cGrey, false);

	Play::DrawDebugText({ DISPLAY_WIDTH * 0.025f, DISPLAY_HEIGHT * 0.05f }, "Overall Time:", Play::cRed, false);
	Play::DrawDebugText({ DISPLAY_WIDTH * 0.135f, DISPLAY_HEIGHT * 0.05f }, DEBUG_TEXT(Time::GetOverallTime()), Play::cRed, false);

	Play::DrawDebugText({ DISPLAY_WIDTH * 0.025f, DISPLAY_HEIGHT * 0.1f }, "App State Time:", Play::cRed, false);
	Play::DrawDebugText({ DISPLAY_WIDTH * 0.135f, DISPLAY_HEIGHT * 0.1f }, DEBUG_TEXT(Time::GetAppStateTime()), Play::cRed, false);
}