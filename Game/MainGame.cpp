#define PLAY_IMPLEMENTATION
#include "Play.h"
#include "Common.h"

#include "ApplicationManager.h"

const int DISPLAY_WIDTH = 1280;
const int DISPLAY_HEIGHT = 720;
const int DISPLAY_SCALE = 1;

void MainGameEntry(PLAY_IGNORE_COMMAND_LINE)
{
	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);
	Play::LoadBackground("Data\\Backgrounds\\Background.png");
	Play::CentreAllSpriteOrigins();
}

bool MainGameUpdate(float elapsedTime)
{
	ApplicationManager::Instance().Update(elapsedTime);
	ApplicationManager::Instance().Draw();

	Play::PresentDrawingBuffer();
	return Play::KeyDown(VK_ESCAPE);
}

int MainGameExit(void)
{
	Play::DestroyManager();
	return PLAY_OK;
}