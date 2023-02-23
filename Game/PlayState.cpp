#include "Play.h"

#include "PlayState.h"
#include "MenuState.h"
#include "VirtualKeys.h"
#include "Common.h"
#include "..\..\MouseEditor\ReadCSV.h"
#include "GameManager.h"

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
}
