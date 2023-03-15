#include "Play.h"
#include "Debug.h"
#include "GameArea.h"
#include "GameStateTypes.h"
#include "GameManager.h"

void Debug::DrawBoldText(std::string text, Play::Point2f pos)
{
	if (!Debug::s_active)
		return;
	
	Play::DrawDebugText(pos + Play::Point2f{ 2.f, 0.f }, text.c_str(), Play::cWhite);
	Play::DrawDebugText(pos + Play::Point2f{ 0.f, 2.f }, text.c_str(), Play::cWhite);
	Play::DrawDebugText(pos + Play::Point2f{ -2.f, 0.f }, text.c_str(), Play::cWhite);
	Play::DrawDebugText(pos + Play::Point2f{ 0.f, -2.f }, text.c_str(), Play::cWhite);
	Play::DrawDebugText(pos + Play::Point2f{ 1.f, 1.f }, text.c_str(), Play::cWhite);
	Play::DrawDebugText(pos + Play::Point2f{ 1.f, -1.f }, text.c_str(), Play::cWhite);
	Play::DrawDebugText(pos + Play::Point2f{ -1.f, 1.f }, text.c_str(), Play::cWhite);
	Play::DrawDebugText(pos + Play::Point2f{ -1.f, -1.f }, text.c_str(), Play::cWhite);

	Play::DrawDebugText(pos + Play::Point2f{ 1.f, 0.f }, text.c_str(), Play::cRed);
	Play::DrawDebugText(pos + Play::Point2f{ 0.f, 1.f }, text.c_str(), Play::cRed);
	Play::DrawDebugText(pos + Play::Point2f{ -1.f, 0.f }, text.c_str(), Play::cRed);
	Play::DrawDebugText(pos + Play::Point2f{ 0.f, -1.f }, text.c_str(), Play::cRed);
}

void Debug::DrawGameAreaObjectDebugInfo()
{
	if (!s_active)
		return;

	for (int x = 0; x < GRID_WIDTH; x++)
	{
		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			GameAreaObject& obj = *GM_INST.m_gameArea->m_gameAreaObjects[x][y];

			if (obj.id == 7) //Rotatey block
			{
				// Rotation
				DrawDebugText(GameArea::GameToWorld({ obj.posx, obj.posy }), std::to_string(obj.rot).c_str(), Play::cRed);

				// Valid directions
				Point2D start = GameArea::GameToWorld({ obj.posx, obj.posy });

				Point2D endTop = start + Point2D{ 0.f, 25.f };
				Point2D endBottom = start + Point2D{ 0.f, -25.f };
				Point2D endRight = start + Point2D{ 25.f, 0.f };
				Point2D endLeft = start + Point2D{ -25.f, 0.f };

				bool validDirs[4] = { (bool)(obj.validEntryDirections & 0x1), (bool)(obj.validEntryDirections >> 1 & 0x1), (bool)(obj.validEntryDirections >> 2 & 0x1), (bool)(obj.validEntryDirections >> 3 & 0x1) };
					
				//// Don't draw if no valid directions
				//if (!validDirs[0] && !validDirs[1] && !validDirs[2] && !validDirs[3])
				//	return;

				if (validDirs[0])
					DrawLine(start, endTop, Play::cGreen);
				else
					DrawLine(start, endTop, Play::cRed);

				if (validDirs[1])
					DrawLine(start, endRight, Play::cGreen);
				else
					DrawLine(start, endRight, Play::cRed);

				if (validDirs[2])
					DrawLine(start, endBottom, Play::cGreen);
				else
					DrawLine(start, endBottom, Play::cRed);

				if (validDirs[3])
					DrawLine(start, endLeft, Play::cGreen);
				else
					DrawLine(start, endLeft, Play::cRed);

			}
		}
	}
}
