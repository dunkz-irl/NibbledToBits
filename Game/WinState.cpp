#include "Play.h"
#include "Common.h"
#include "Debug.h"
#include "Button.h"
#include "EasingFunctions.h"
#include "ParticleManager.h"

#include "WinState.h"

void WinState::OnEnter()
{
	using namespace Play;

	m_debugStateName = "Win State";
	Vector2D buttonSize = { 367.f, 112.f };

	m_continueButtonPos = CENTRE_POINT;
	m_continueButtonPos.x -= buttonSize.x / 2.f;
	m_continueButtonPos.y -= buttonSize.y / 2.f;
	m_continueButtonPos.y -= 100.f;

	m_continueButton = new Button{ Play::GetSpriteId("continue-unpressed"), m_continueButtonPos, buttonSize };

	// #TODO: Confetti particles

	Play::Point2f offset = { 300.f, 0.f };

	ParticleManager::Instance().CreateEmitter(EmitterType::CONFETTI, Play::Point2f CENTRE_POINT - offset, 0.1f);
	ParticleManager::Instance().CreateEmitter(EmitterType::CONFETTI, Play::Point2f CENTRE_POINT + offset, 0.1f);
}

IGameState* WinState::OnUpdate()
{
	if (m_continueButton->Pressed())
	{
		m_continueButton->SetSprite("continue-pressed");
	}
	return nullptr;
}

void WinState::OnDraw()
{
	float t = GetStateTime();
	float duration = 1.3f;
	float scale = 1.3f;

	if (t <= duration)
	{
		Play::DrawSpriteRotated("win-text", Play::Point2f CENTRE_POINT - Play::Point2f{ 0.f, -35.f }, 0, 0, EaseOutElastic(t / duration) * scale);
	}
	else
	{
		Play::DrawSpriteRotated("win-text", Play::Point2f CENTRE_POINT - Play::Point2f{ 0.f, -35.f }, 0, 0, scale);
	}

	t -= 0.1f; // Delay between animations starting

	if (t <= duration && !(t < 0))
	{
		Play::DrawSpriteRotated("continue-unpressed", Play::Point2f CENTRE_POINT - Play::Point2f{ 0.f, 100.f }, 0, 0, EaseOutElastic(t / duration));
	}
	else if (t > duration)
	{
		m_continueButton->Draw();
	}

	Play::DrawFontText("ABNORMAL40px_10x10", "Continue", Play::Point2f CENTRE_POINT - Play::Point2f{ 0.f, 100.f }, Play::CENTRE);
}

void WinState::OnExit()
{
	delete m_continueButton;
}
