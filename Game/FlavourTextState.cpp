#include "Play.h"
#include "Common.h"

#include "Button.h"
#include "Time.h"
#include "MainGameState.h"
#include "VirtualKeys.h"

#include "FlavourTextState.h"

FlavourTextState::FlavourTextState(const char* textFile)
{
	m_textFile = textFile;
	m_debugStateName = "Flavour Text";
}

void FlavourTextState::OnEnter()
{
	Play::PlayAudio("fanfare");
	// Temp audio (doesn't really work)
	//Play::PlayAudio("title");

	m_continueButton = new Button{ Play::GetSpriteId("tick_panel"), { DISPLAY_WIDTH * 0.85f, DISPLAY_HEIGHT * 0.1f }, {100.f, 100.f} };

	m_vLines.push_back(std::string());
	m_vLinePositions.push_back({ DISPLAY_WIDTH * 0.1f, DISPLAY_HEIGHT * 0.9f });

	// Load story text
	std::ifstream introFile("data/" + m_textFile);	
	PLAY_ASSERT_MSG(introFile, "No text file!");
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

	introFile.close();
}

void FlavourTextState::OnExit()
{
	delete m_continueButton;
	// delete story text
}

IApplicationState* FlavourTextState::OnUpdate()
{
	if (m_charIndex == m_introText.length())
	{
		if (m_continueButton->Pressed())
		{
			return new MainGameState();
		}

		return nullptr;
	}

	if (Play::KeyPressed(VK_SPACE))
	{
		return new MainGameState();
	}


	m_timer += Time::GetElapsedTime();

	float m_offsetCharDelay = m_charDelay + static_cast<float>(Play::RandomRollRange(-100, 100)) / 1000.f;

	if (m_timer > m_offsetCharDelay)
	{
		std::string typingSFX = "type-";
		typingSFX.append(std::to_string(Play::RandomRoll(13)));
		
		m_vLines[m_lineIndex].append(m_introText, m_charIndex, 1);

		if (m_introText[m_charIndex] == ' ')
		{
			Play::PlayAudio("space");
		}
		else
		{
			Play::PlayAudio(typingSFX.c_str());
		}

		m_timer = 0.f;
		m_charIndex++;
		if (m_introText[m_charIndex] == '\n')
		{
			m_vLines.push_back(std::string());
			m_vLinePositions.push_back(m_vLinePositions[m_lineIndex]);
			m_lineIndex++;
			m_vLinePositions[m_lineIndex].y -= 75.f;
			m_charIndex++;
			Play::PlayAudio("ding");
			m_timer = -0.5f;
		}
	}

	return nullptr;
}

void FlavourTextState::OnDraw()
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
