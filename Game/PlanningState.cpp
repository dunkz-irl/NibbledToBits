#include "Play.h"
 
#include "ParticlesCommon.h"
#include "PlanningState.h"
#include "GoState.h"
#include "PauseState.h"
#include "GameArea.h"
#include "Time.h"

#include "GameManager.h"

#include "VirtualKeys.h"

void PlanningState::OnEnter()
{
	GM_INST.m_currentGameState = GAMESTATE_ENUM::PLANNING;
}

void PlanningState::OnExit()
{
	IGameState::OnExit();
}

IGameState* PlanningState::OnUpdate()
{
	if (m_proceedToNextState)
	{
		return new GoState();
	}

	if (Play::KeyPressed(VK_P))
	{
		return new PauseState();
	}

	return nullptr;
}

void PlanningState::OnDraw()
{
	GM_INST.DrawHeldItem();
	GM_INST.DrawStartButton();
	GM_INST.DrawUI();

	// Draw bouncy direction arrows
	DrawMouseHoleArrows();

	// throw std::logic_error("The method or operation is not implemented.");
}

void PlanningState::DrawMouseHoleArrows()
{
	GameAreaObject* mouseHole = GM_INST.GetEntryObj();
	std::string sprite = "goarrow_RA";
	//std::string suffix;
	GridPos pos;
	Matrix2D matrix;
	float rot = 0.f;

	float t = Time::GetGameStateTime() * 10.f;

	for (int i = 0; i < 2; i++)
	{
		matrix = MatrixIdentity();

		if (mouseHole->posx == -1) // Hole is on left border
		{
			rot = PLAY_PI / 2.f;
			pos = { 0, mouseHole->posy };
		}
		else if (mouseHole->posx == 17) // Hole is on right border
		{
			rot = PLAY_PI * 1.5f;
			pos = { 16, mouseHole->posy };
		}
		else if (mouseHole->posy == -1) // Hole is on bottom border
		{
			rot = PLAY_PI;
			pos = { mouseHole->posx, 0 };
		}
		else if (mouseHole->posy == 14) // Hole is on top border
		{
			rot = 0.f;
			pos = { mouseHole->posx, 13 };
		}

		matrix.row[2] = GameArea::GameToWorld({ pos.x, pos.y });
		matrix.row[2] += RotateVector(Vector2f(0.f, sin(t) * 4.f) * 2.f, rot);
		matrix = matrix * MatrixRotation(rot);
		matrix = matrix * MatrixScale((sin(t) / 8.f) + 0.8f, (cos(t) / 4.f) + 0.8f);

		if (i == 1) // Flip sprite
		{
			matrix = matrix * MatrixScale(-1.f, -1.f);
		}

		Play::DrawSpriteTransformed(Play::GetSpriteId(sprite.c_str()), matrix, 0);

		mouseHole = GM_INST.GetExitObj(); // On second iteration, draw exit
	}
}