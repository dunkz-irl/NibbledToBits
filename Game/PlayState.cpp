#include "Play.h"

#include "PlayState.h"
#include "MenuState.h"
#include "VirtualKeys.h"
#include "Common.h"

void PlayState::OnEnter()
{

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
