#include "Play.h"
#include "LoadLevel.h"
#include "Common.h"

// GameAreaObjects
#include "SingleWall.h"
#include "RotatingBlock.h"
#include "MouseHoleEntry.h"
#include "MouseHoleExit.h"
#include "MouseTrap.h"
#include "EmptySquare.h"

#include "GameAreaObjects.h"

#include "GameArea.h"
#include "PanelItem.h"
#include "Panel.h"
#include "ReadCSV.h"
#include "GameManager.h"
#include "CheesePickup.h"
#include <queue>
#include "Tank.h"
#include "AmmoPickup.h"

std::vector<ObjectCSV> g_vObjects;
std::map<std::string, int> g_idMap;
std::vector<std::string> g_v_idToStringTable;

GameAreaObject* g_initObj = nullptr;

std::vector<std::string> LevelLoader::TokeniseStringByComma(std::string line)
{
	std::istringstream ss(line);
	std::vector<std::string> tokens;
	std::string token;

	while (std::getline(ss, token, ','))
	{
		tokens.push_back(token);
	}

	return tokens;
}

void LevelLoader::LoadLevel(const char* levelName)
{
	std::string path = "data/";
	path.append(levelName);

	std::ifstream levelFile(path);

	std::string line;
	std::vector<std::string> tokens;

	// Skip first line (header?)
	std::getline(levelFile, line);

	// Line 1 is entrance(?)
	std::getline(levelFile, line);
	tokens.clear();
	tokens = TokeniseStringByComma(line);
	GM_INST.m_gameArea->m_holeEntry->posx = std::stoi(tokens[0]);
	GM_INST.m_gameArea->m_holeEntry->posy = std::stoi(tokens[1]);

	// Line 2 is exit(?)
	std::getline(levelFile, line);
	tokens.clear();
	tokens = TokeniseStringByComma(line);
	GM_INST.m_gameArea->m_holeExit->posx = std::stoi(tokens[0]);
	GM_INST.m_gameArea->m_holeExit->posy = std::stoi(tokens[1]);

	// Line 3 is number of mice, mouse spawn rate, and target mice, separated by commas
	std::getline(levelFile, line);
	tokens.clear();
	tokens = TokeniseStringByComma(line);
	GM_INST.m_numLevelMice = std::stoi(tokens[0]);
	GM_INST.m_mouseSpawnRate = std::stof(tokens[1]);
	GM_INST.m_targetSavedMice = std::stoi(tokens[2]);

	// Populate objects in the level

	// Temp thingy
	GameAreaObject* gameAreaObjects[GRID_WIDTH][GRID_HEIGHT]; // To put in m_GameArea

	// Initialise GAObjs
	if (!g_initObj)
	{
		g_initObj = new EmptySquare();
	}

	for (int x = 0; x < GRID_WIDTH; x++)
	{
		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			gameAreaObjects[x][y] = g_initObj;	// All the "uninitialised" entries are the same, so why not all point to a single placeholder object
												// rather than creating a new one each time.
		}
	}

	while (levelFile)
	{
		std::getline(levelFile, line);

		// Ignore empty lines
		if (line.empty()) {
			continue;
		}

		tokens.clear();
		tokens = TokeniseStringByComma(line);

		// Exit the loop when reaching the "Inventory" line
		if (tokens[0] == "Inventory")
		{
			break;
		}

		GameAreaObject* obj = nullptr;

		obj = CreateNewGameAreaObjectOfType(tokens);

		gameAreaObjects[obj->posx][obj->posy] = obj;
		// GameManager::Instance().m_vGameAreaObjects.push_back(obj);
	}

	// Populate player inventory
	while (levelFile)
	{
		std::getline(levelFile, line);
		if (line.empty()) {
			continue;
		}

		tokens.clear();
		tokens = TokeniseStringByComma(line);

		if (std::stoi(tokens[1]) == 0) // If no items of type in inventory
		{
			continue;
		}

		InventoryPair invPair{ tokens[0], std::stoi(tokens[1]) };
		m_vInventoryPairs.push_back(invPair);
	}

	std::vector<ObjectCSV> v_CSVobjects = ReadObjectsCSV();
	std::vector<ObjectCSV> v_inventory;

	// Check ID (string) of each item in the GM inventory, which has already read from the level file
	for (InventoryPair invPair : m_vInventoryPairs)
	{
		// Remove inventory items of which player has none, for constructing the game panel with
		for (ObjectCSV object : v_CSVobjects)
		{
			int invObjID = g_idMap[invPair.first];

			if (invObjID == object.id)
			{
				v_inventory.push_back(object);
			}
		}
	}

	// Make all objects have the category INVENTORY so they appear on the same page
	for (ObjectCSV& object : v_inventory)
	{
		object.group = ItemType::INVENTORY;
	}

	if (GM_INST.m_panel)
	{
		delete GM_INST.m_panel;
	}

	GM_INST.m_panel = new Panel(v_inventory);

	// UGH create a vector that can be used by the below panel function to set the correct quantities of items
	std::vector<std::tuple<int, int>> v_tempInventory;
	for (InventoryPair invPair : m_vInventoryPairs)
	{
		std::tuple<int, int> t = { g_idMap[invPair.first], invPair.second };
		v_tempInventory.push_back(t);
	}

	// Set entry directions for gameAreaObjects
	for (ObjectCSV& csv_obj : v_CSVobjects)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			for (int y = 0; y < GRID_HEIGHT; y++)
			{
				GameAreaObject* ga_obj = gameAreaObjects[x][y];
				if (ga_obj->id == csv_obj.id)
				{
					ga_obj->possibleEntryDirections = csv_obj.entryDirections;
				}
			}
		}
	}

	// Add object to GameArea objects (only do this once)
	GM_INST.m_gameArea->SetGameAreaObjects(gameAreaObjects);
	GM_INST.m_panel->SetPlayerInventory(v_tempInventory);

	// Have to do this after the GameArea member array has been copied into
	for (int x = 0; x < GRID_WIDTH; x++)
	{
		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			GameAreaObject& obj = *GameArea::m_gameAreaObjects[x][y];

			// Match entryDirections to object rotation value
			int i = 0;

			do 
			{
				if (obj.rot != 0)
				{
					GameArea::RotateEntryDirections(obj.possibleEntryDirections);
				}
				GameArea::ValidateEntryDirections(obj);
				i++;
			} while (i < obj.rot);
		}
	}
}

GameAreaObject* LevelLoader::CreateNewGameAreaObjectOfType(std::vector<std::string> tokens)
{
	GameAreaObject* pGAObj = nullptr;

	// #NewObjects
	// Create object of correct type
	switch (g_idMap[tokens[0]])
	{
		case SINGLE:
			pGAObj = new SingleWall();
			break;
		case TUBE_TWO_WAY:
			pGAObj = new RotatingBlock();
			break;
		case TRAP_01_SET:
			pGAObj = new MouseTrap();
			break;
		case EMMENTAL:
		case BRIE:
		case PARMESAN:
			GM_INST.m_targetCheese++;
			pGAObj = new CheesePickup();
			break;
		case SUNFLOWERSEED:
		case CORNKERNEL:
		case GRAPE:
		case RASPBERRY:
			pGAObj = new AmmoPickup();
			break;
		case TANK:
			pGAObj = new Tank();
			break;
		default:
			pGAObj = new GameAreaObject();
			break;
	}

	pGAObj->id = g_idMap[tokens[0]];		// String ID -- const char * is a pointer so when obj is destroyed that memory becomes nonsense! Can't take a copy as with string
	pGAObj->posx = std::stoi(tokens[1]);	// X position
	pGAObj->posy = std::stoi(tokens[2]);	// Y position
	pGAObj->rot = std::stoi(tokens[3]);		// Rotation (not an angle but in 90 degrees ness)
	pGAObj->misc = std::stoi(tokens[4]);	// Misc variable
	pGAObj->mouseHole = false;				// mouse hole #Duncan not sure if this is bad
	pGAObj->pickupable = false;				// Level items shouldn't be pickupable

	// Using the misc variable to allow the player to rotate certain level-placed items
	if (pGAObj->misc != 1) // #TODO: Magic number, maybe make an enum?
	{
		pGAObj->rotatable = false;		// or rotatable
	}

	return pGAObj;
}
