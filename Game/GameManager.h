#pragma once

class GameArea;
class Panel;
class GoButton;
struct FloatingObject;
class IGameState;

class GameObject;
class GameObjectFactory;

struct GridPoint { int x; int y; };

#define GM_INST GameManager::Instance()

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

	void ToNextState();

	GameObject* GetGameObject(int id);

	GridPoint GetEntrancePosition();
	GridPoint GetExitPosition();

	friend class MainGameState;
	friend class LevelLoader;
	friend class GameObjectFactory;
	friend class Time;

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
	GameArea* m_gameArea = nullptr;
	Panel* m_panel = nullptr;
	FloatingObject* m_currentHeld = nullptr;

	std::vector<int> m_vGameObjectIDs;

	// #TODO Maybe a UI manager class makes more sense for this.
	// Start/stop UI
	GoButton* m_goButton = nullptr;

	IGameState* m_pGameState = nullptr;

};
