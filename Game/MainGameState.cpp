#include "Play.h"

#include "Common.h"
#include "VirtualKeys.h"

#include "MainGameState.h"
#include "MenuState.h"

#include "ReadCSV.h"
#include "GameArea.h"
#include "PanelItem.h"
#include "Panel.h"

#include "GameObjectFactory.h"
#include "GameManager.h"

// #TODO: Not a great place to include these
extern std::vector<ObjectCSV> g_vObjects;

void MainGameState::OnEnter()
{
	m_debugStateName = "Main Game";

	// Load level
	g_vObjects = ReadObjectsCSV();
	GM_INST.LoadLevel("LEVEL1.lev");

	// #TODO: Test stuff
	GameObjectFactory::Create(GameObjectType::TYPE_MOUSE, CENTRE_POINT);
}

void MainGameState::OnExit()
{
	GM_INST.Destroy();
}

IApplicationState* MainGameState::OnUpdate()
{
	if (Play::KeyPressed(VK_M))
	{
		return new MenuState();
	}

	GM_INST.ManageInput(); // #TODO: Should buttons/UI be in here?

	// Fagin/Abdullah's stuff
	GM_INST.m_gameArea->Update();
	GM_INST.m_panel->Update();

	// My stuff
	GM_INST.Update();

	return nullptr;
}

void MainGameState::OnDraw()
{
	Play::DrawBackground();
	GM_INST.DrawHeldItem();
	GM_INST.m_gameArea->DrawGameArea();
	GM_INST.m_panel->Draw();
	GM_INST.DrawStartButton();
}