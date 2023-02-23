#pragma once

struct GridPoint { int x; int y; };

typedef std::pair<std::string, int> InventoryPair;

struct LevelObject
{
	std::string id{ "" };
	GridPoint gridPos{ 0,0 };
	float rot{ 0 };
	int var{ 0 };
};

class GameManager
{

public:
	
	// Singleton /////
	static GameManager& Instance();
	static void Destroy();
	//////////////////

	void Update();
	void LoadLevel(const char* levelName);

	GridPoint GetEntrancePosition();
	GridPoint GetExitPosition();

private:

	// Singleton /////	
	GameManager();
	~GameManager();
	static GameManager* s_pInstance;

	GameManager& operator=(const GameManager) = delete;
	GameManager(const GameManager&) = delete;
	//////////////////

	//GameArea m_gameArea;
	//Panel m_panel;

	// Level loadereeny
	// Functerinos
	std::vector<std::string> TokeniseStringByComma(std::string);

	// Variablamos
	GridPoint m_entrancePosition{ -2, -2 }; // -1 can be valid
	GridPoint m_exitPosition{ -2, -2 };
	std::vector<LevelObject> m_vLevelObjects;
	std::vector<InventoryPair> m_vInventoryPairs;
};

