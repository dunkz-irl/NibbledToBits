#include "Play.h"
#include "MenuState.h"
#include "GameArea.h"
#include "GameManager.h"

GameManager* GameManager::s_pInstance = nullptr;
extern std::map<std::string, int> idMap;

GameManager::GameManager()
{
	s_pInstance = this;
}

GameManager::~GameManager()
{
	s_pInstance = nullptr;
}

GameManager& GameManager::Instance()
{
	if (!s_pInstance)
	{
		s_pInstance = new GameManager;
	}

	return *s_pInstance;
}

void GameManager::Destroy()
{

}

void GameManager::Update()
{

}

void GameManager::LoadLevel(const char * levelName)
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
	m_entrancePosition = { std::stoi(tokens[0]), std::stoi(tokens[1]) };

	// Line 2 is exit(?)
	std::getline(levelFile, line);
	tokens.clear();
	tokens = TokeniseStringByComma(line);
	m_exitPosition = { std::stoi(tokens[0]), std::stoi(tokens[1]) };

	// Populate objects in the level

	// Temp thingy
	GameAreaObject objects[16][13]; // To put in m_GameArea

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
			idMap[tokens[0]],								// String ID -- const char * is a pointer so when obj is destroyed that memory becomes nonsense! Can't take a copy as with string
			std::stoi(tokens[1]),							// X position
			std::stoi(tokens[2]),							// Y position
			std::stoi(tokens[3]),							// Rotation (not an angle but in 90 degrees ness)
			std::stoi(tokens[4])							// Misc variable
		};

		objects[obj.posx][obj.posy] = obj;
		GameManager::Instance().m_vGameAreaObjects.push_back(obj);
	}

	// Add object to GameArea objects (only do this once)
	m_gameArea.SetGameAreaObjects(objects);
	
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
			
		InventoryPair invPair{tokens[0], std::stoi(tokens[1])};
		m_vInventoryPairs.push_back(invPair);
	}
}

std::vector<std::string> GameManager::TokeniseStringByComma(std::string line)
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

GridPoint GameManager::GetEntrancePosition()
{
	if (!(m_entrancePosition.x < -1) && !(m_entrancePosition.y < -1))
	{
		return m_entrancePosition;
	}
	else
	{
		PLAY_ASSERT_MSG(false, "Entrance position is invalid.")
		return { -2, -2 };
	}
}

GridPoint GameManager::GetExitPosition()
{
	if (!(m_exitPosition.x < -1) && !(m_exitPosition.y < -1))
	{
		return m_exitPosition;
	}
	else
	{
		PLAY_ASSERT_MSG(false, "Exit position is invalid.")
		return { -2, -2 };
	}
}