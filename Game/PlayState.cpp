#include "Play.h"

#include "Common.h"
#include "VirtualKeys.h"

#include "PlayState.h"
#include "MenuState.h"

#include "ReadCSV.h"
#include "GameArea.h"
#include "PanelItem.h"
#include "Panel.h"

#include "GameManager.h"

#define GM_INST GameManager::Instance()

// #TODO: Not a great place to include these
extern std::vector<ObjectCSV> objects;
extern std::map<std::string, int> idMap;
extern std::vector<std::string> idToString;

void PlayState::OnEnter()
{
	// Load level
	objects = ReadObjectsCSV();
	GameManager::Instance().LoadLevel("TEST.lev");
}

void PlayState::OnExit()
{

}

IGameState* PlayState::OnUpdate()
{
	if (Play::KeyPressed(VK_M))
	{
		return new MenuState();
	}

	return nullptr;
}

void PlayState::OnDraw()
{
	Play::DrawBackground();
	GM_INST.m_gameArea.DrawGameArea();
}
