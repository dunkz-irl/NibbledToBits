#include "Play.h"
#include "Debug.h"

void Debug::DrawBoldText(std::string text, Play::Point2f pos)
{
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
