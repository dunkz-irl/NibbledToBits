#include "Play.h"
#include "LoadLevel.h"
#include "GameArea.h"
#include "PanelItem.h"
#include "Panel.h"
#include "ReadCSV.h"
#include "GameManager.h"

std::vector<ObjectCSV> g_vObjects;
std::map<std::string, int> g_idMap;
std::vector<std::string> g_v_idToStringTable;

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
	GM_INST.m_gameArea->m_holeEntry.posx = std::stoi(tokens[0]);
	GM_INST.m_gameArea->m_holeEntry.posy = std::stoi(tokens[1]);

	// Line 2 is exit(?)
	std::getline(levelFile, line);
	tokens.clear();
	tokens = TokeniseStringByComma(line);
	GM_INST.m_gameArea->m_holeExit.posx = std::stoi(tokens[0]);
	GM_INST.m_gameArea->m_holeExit.posy = std::stoi(tokens[1]);

	// Line 3 is number of mice, and mouse spawn rate separated by commas
	std::getline(levelFile, line);
	tokens.clear();
	tokens = TokeniseStringByComma(line);
	GM_INST.m_numLevelMice = std::stoi(tokens[0]);
	GM_INST.m_mouseSpawnRate = std::stof(tokens[1]);

	// Populate objects in the level

	// Temp thingy
	GameAreaObject gameAreaObjects[16][13]; // To put in m_GameArea

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

		// Make an object out of the current line
		GameAreaObject obj
		{
			g_idMap[tokens[0]],		// String ID -- const char * is a pointer so when obj is destroyed that memory becomes nonsense! Can't take a copy as with string
			std::stoi(tokens[1]),	// X position
			std::stoi(tokens[2]),	// Y position
			std::stoi(tokens[3]),	// Rotation (not an angle but in 90 degrees ness)
			std::stoi(tokens[4]),	// Misc variable
		};

		obj.pickupable = false;		// Level items shouldn't be pickupable

		// Using the misc variable to allow the player to rotate certain level-placed items
		if (obj.misc != 1) // #TODO: Magic number, maybe make an enum?
		{
			obj.rotatable = false;		// or rotatable
		}

		gameAreaObjects[obj.posx][obj.posy] = obj;
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

	// Remove inventory items of which player has none, for constructing the game panel with
	for (ObjectCSV object : v_CSVobjects)
	{
		// Check ID (string) of each item in the GM inventory, which has already read from the level file
		for (InventoryPair invPair : m_vInventoryPairs)
		{
			// First character is capital and needs to be changed
			std::string str_objNameLower = object.name;        // #TODO ~ What nonsense is this pray tell! ~
			char c = std::tolower(str_objNameLower[0]);
			str_objNameLower.front() = c;
			std::erase(invPair.first, ' ');

			if (invPair.first == str_objNameLower)
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
		for (int x = 0; x < 16; x++)
		{
			for (int y = 0; y < 13; y++)
			{
				GameAreaObject& ga_obj = gameAreaObjects[x][y];
				if (ga_obj.id == csv_obj.id)
				{
					ga_obj.possibleEntryDirections = csv_obj.entryDirections;
					
					// Match entryDirections to object rotation value
					for (int i = 0; i < ga_obj.rot; i++)
					{
						GameArea::RotateEntryDirections(ga_obj.possibleEntryDirections);
						GameArea::ValidateEntryDirections(ga_obj);
					}
				}
			}
		}
	}

	// Add object to GameArea objects (only do this once)
	GM_INST.m_gameArea->SetGameAreaObjects(gameAreaObjects);
	GM_INST.m_panel->SetPlayerInventory(v_tempInventory);
}