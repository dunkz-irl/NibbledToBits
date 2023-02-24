#pragma once

struct GridPoint { int x; int y; };

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
	void ManageInput();
	void DrawHeldItem();

	GridPoint GetEntrancePosition();
	GridPoint GetExitPosition();

	friend class PlayState;
	friend class LevelLoader;

private:

	// Singleton /////	
	GameManager();
	~GameManager();
	static GameManager* s_pInstance;

	GameManager& operator=(const GameManager) = delete;
	GameManager(const GameManager&) = delete;
	//////////////////
	
	// Functerinos
	std::vector<std::string> TokeniseStringByComma(std::string);

	// Variablamos
	GameArea m_gameArea{};
	Panel m_panel;
	FloatingObject m_currentHeld;

	//std::vector<GameAreaObject> m_vGameAreaObjects; // I think m_gameArea.m_gameAreaObjects does this job, but I'll see for a bit

};
