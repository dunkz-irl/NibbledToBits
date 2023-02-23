#include "Play.h"
#include "MenuState.h"
#include "PlayState.h"
#include "Common.h"
#include "VirtualKeys.h"

void MenuState::OnEnter()
{

}

void MenuState::OnExit()
{

}

IGameState* MenuState::OnUpdate()
{
	if (Play::KeyPressed(VK_P))
	{
		return new PlayState();
	}

	m_testCounter++;
	return nullptr;
}

void MenuState::OnDraw()
{
	Play::ClearDrawingBuffer(Play::cBlack);
	Play::DrawSprite("title", { DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT * 0.6f }, 0);
	Play::DrawDebugText(CENTRE_POINT, DEBUG_TEXT(m_testCounter), Play::cWhite);
	Play::DrawDebugText({ DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT * 0.25f }, "Press P to Play", Play::cWhite);
}