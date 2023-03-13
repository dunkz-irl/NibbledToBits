#pragma once

class GameArea;
class Panel;
class GoButton;
struct FloatingObject;
class IGameState;
class PauseState;
struct GameAreaObject;

struct GridVector;
class GameObject;
class GameObjectManager;

struct GridPoint { int x; int y; };

#define GM_INST GameManager::Instance()

enum class GAMESTATE_ENUM
{
	PLANNING = 0,
	GO,
	PAUSE
};

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
	void Draw();
	void LoadLevel(const char* levelName);
	void ManageInput();
	void DrawHeldItem();

	void UpdateStartButton();
	void DrawStartButton();

	void UpdateGameObjects();

	void ToNextState();

	void NextLevel();

	GameObject* GetGameObject(int id);

	void DrawUI();

	Play::Point2D GetEntrancePosition();
	GridPoint GetExitPosition();
	GameAreaObject* GetEntryObj();

	std::pair<int, float> GetMouseSpawnInfo();

	GAMESTATE_ENUM m_currentGameState{GAMESTATE_ENUM::PLANNING};
	std::string m_previousGameStateString{ "" };

	friend class MainGameState;
	friend class GoState;
	friend class LevelLoader;
	friend class GameObjectManager;
	friend class Time;
	friend class GameArea;
	friend class Debug;
	
	void IncrementCollectedCheese();
private:

	// Singleton /////	
	GameManager();	//
	~GameManager();	//
	static GameManager* s_pInstance;
	//				//
	GameManager& operator=(const GameManager) = delete;
	GameManager(const GameManager&) = delete;
	//////////////////
	
	// Functerinos
	std::vector<std::string> TokeniseStringByComma(std::string);

	// Variablamos
	GameArea* m_gameArea = nullptr;
	Panel* m_panel = nullptr;
	FloatingObject* m_currentHeld = nullptr;

	std::vector<int> m_vGameObjectIDs;

	// #TODO Maybe a UI manager class makes more sense for this.
	// Start/stop UI
	GoButton* m_goButton = nullptr;

	IGameState* m_pGameState = nullptr;
	PauseState* m_pauseState;

	int m_numLevelMice;
	float m_mouseSpawnRate;
	int m_targetSavedMice;
	int m_savedMice; // Follows the variable in GoState.cpp
	int m_level{ 0 };

	const char* m_levelStrings[2]{ "LEVEL1.LEV", "LEVEL2.LEV" };

	int m_collectedCheese{ 0 };
	int m_targetCheese{ 0 };
public:
	GameAreaObject* GetExitObj();
	void RemoveGameAreaObject(GridVector gridPos);
};
