#include "Play.h"
#include "Common.h"
#include "VirtualKeys.h"

#include "MenuState.h"
#include "MainGameState.h"

#include "MouseGraphic.h"
#include "TitleTextGraphic.h"
#include "EasingFunctions.h"

void MenuState::OnEnter()
{
	Play::CentreAllSpriteOrigins();

	TitleTextGraphic* titleTextGraphic = new TitleTextGraphic{ { DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT * 0.6f }, Play::GetSpriteId("title")};
	m_vSimpleGraphics.push_back(titleTextGraphic);

	MouseGraphic* mouseGraphic = new MouseGraphic({ DISPLAY_WIDTH * 0.8f, DISPLAY_HEIGHT * 0.2f }, Play::GetSpriteId("remi"));
	m_vSimpleGraphics.push_back(mouseGraphic);
}

void MenuState::OnExit()
{
	for (SimpleGraphic* pGraphic : m_vSimpleGraphics)
	{
		delete pGraphic;
	}
}

IApplicationState* MenuState::OnUpdate()
{
	for (SimpleGraphic* pGraphic : m_vSimpleGraphics)
	{
		pGraphic->Update();
	}

	if (Play::KeyPressed(VK_P))
	{
		return new MainGameState();
	}

	m_testCounter++;
	return nullptr;
}

void MenuState::OnDraw()
{
	Play::ClearDrawingBuffer(Play::cBlack);

	for (SimpleGraphic* pGraphic : m_vSimpleGraphics)
	{
		pGraphic->Draw();
	}

	// Play::DrawSprite("title", { DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT * 0.6f }, 0);
	Play::DrawDebugText(CENTRE_POINT, DEBUG_TEXT(m_testCounter), Play::cWhite);
	Play::DrawDebugText({ DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT * 0.25f }, "Press P to Play", Play::cWhite);
}