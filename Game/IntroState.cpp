#include "Play.h"
#include "Common.h"

#include "Button.h"
#include "Time.h"
#include "MainGameState.h"

#include "IntroState.h"

void IntroState::OnEnter()
{
	// Temp audio (doesn't really work)
	//Play::PlayAudio("title");

	m_continueButton = new Button{ Play::GetSpriteId("tick_panel"), { DISPLAY_WIDTH * 0.85f, DISPLAY_HEIGHT * 0.1f }, {100.f, 100.f} };

	m_vLines.push_back(std::string());
	m_vLinePositions.push_back({ DISPLAY_WIDTH * 0.1f, DISPLAY_HEIGHT * 0.9f });

	// Load story text
	std::ifstream introFile("data/intro.txt");	
	PLAY_ASSERT_MSG(introFile, "No intro text file!");
	std::string line;

	while (introFile)
	{
		std::getline(introFile, line);

		// Ignore empty lines
		if (line.empty()) {
			continue;
		}

		m_introText.append(line);
		m_introText.append("\n");
	}
}

void IntroState::OnExit()
{
	delete m_continueButton;
	// delete story text
}

IApplicationState* IntroState::OnUpdate()
{
	if (m_charIndex == m_introText.length())
	{
		if (m_continueButton->Pressed())
		{
			return new MainGameState();
		}

		return nullptr;
	}

	m_timer += Time::GetElapsedTime();

	if (m_timer > m_charDelay)
	{
		m_vLines[m_lineIndex].append(m_introText, m_charIndex, 1);

		m_timer = 0.f;
		m_charIndex++;
		if (m_introText[m_charIndex] == '\n')
		{
			m_vLines.push_back(std::string());
			m_vLinePositions.push_back(m_vLinePositions[m_lineIndex]);
			m_lineIndex++;
			m_vLinePositions[m_lineIndex].y -= 75.f;
			m_charIndex++;
		}
	}

	return nullptr;
}

void IntroState::OnDraw()
{
	Play::ClearDrawingBuffer(Play::cBlack);

	if (m_charIndex == m_introText.length())
	{
		m_continueButton->Draw();
	}

	int count = 0;
	for (std::string line : m_vLines)
	{
		Play::DrawFontText("font64px_10x10", line, m_vLinePositions[count]);
		count++;
	}
	
}
