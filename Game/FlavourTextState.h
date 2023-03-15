#pragma once
#include "IApplicationState.h"

class Button;

class FlavourTextState : public IApplicationState
{

public:
	FlavourTextState(const char* textFile);

	void OnEnter() override;


	void OnExit() override;


	IApplicationState* OnUpdate() override;


	void OnDraw() override;

private:
	std::string m_introText;

	std::vector<std::string> m_vLines;
	std::vector<Play::Point2f> m_vLinePositions;
	float m_timer{ 0.f };
	float m_charDelay{ 0.15f };
	int m_charIndex{ 0 };
	int m_lineIndex{ 0 };

	// Play::Point2f m_typingPoint{ DISPLAY_WIDTH * 0.1f, DISPLAY_HEIGHT * 0.9f };
	Button* m_continueButton;
	std::string m_textFile;
};

