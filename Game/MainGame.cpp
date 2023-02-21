#define PLAY_IMPLEMENTATION
#include "Play.h"

int DISPLAY_WIDTH = 1280;
int DISPLAY_HEIGHT = 720;
int DISPLAY_SCALE = 1;

void MainGameEntry(PLAY_IGNORE_COMMAND_LINE)
{
	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE, Play::ANTICLOCKWISE_ZERO_RIGHT, Play::XRIGHT_YUP);
	Play::LoadBackground("Data\\Backgrounds\\Background.png");
	Play::CentreAllSpriteOrigins();
}

bool MainGameUpdate(float elapsedTime)
{
	Play::DrawBackground();
	Play::PresentDrawingBuffer();

	return Play::KeyDown(VK_ESCAPE);
}

int MainGameExit(void)
{
	Play::DestroyManager();
	return PLAY_OK;
}