#pragma once

class GameArea;
class Panel;
class GoButton;
struct FloatingObject;
class IGameState;
class PauseState;

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

	GameObject* GetGameObject(int id);

	Play::Point2D GetEntrancePosition();
	GridPoint GetExitPosition();

	std::pair<int, float> GetMouseSpawnInfo();

	GAMESTATE_ENUM m_currentGameState{GAMESTATE_ENUM::PLANNING};

	friend class MainGameState;
	friend class LevelLoader;
	friend class GameObjectManager;
	friend class Time;
	friend class GameArea;

	
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
};
