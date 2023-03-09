#pragma once
#include "ReadCSV.h"

struct GridPos {
	int x{ 0 };
	int y{ 0 };
};

struct FloatingObject {
	int id{ -1 };
	int rot{ 0 };
	int misc{ 0 };
	bool mouseHole{ false };
};

struct GameAreaObject {

	GameAreaObject(int id = 0, int posx = 0, int posy = 0, int rot = 0, int misc = 0, bool mouseHole = false);
	int id{ -1 };
	int posx{ -2 };
	int posy{ -2 };
	int rot{ 0 };
	int misc{ 0 };
	bool mouseHole{ false };
	bool vis{ true };
	bool pickupable{ true };
	bool rotatable{ true };

	uint8_t possibleEntryDirections{ 0x0 };
	uint8_t validEntryDirections{ 0x0 };

	virtual void OnCurrentSquare(void* pObj) { };
	virtual void OnNextSquare(void* pObj) { };
};

using namespace Play;

extern int GAME_AREA_WIDTH;
extern int GAME_AREA_HEIGHT;
extern int SQUARE_SIZE;
constexpr int GRID_WIDTH{ 16 };
constexpr int GRID_HEIGHT{ 13 };
extern int BOARDER_PIXELS;
extern const int DISPLAY_WIDTH;
extern const int DISPLAY_HEIGHT;
extern int DISPLAY_SCALE;

class MouseHoleEntry;

class GameArea {
private:
	GridPos GetMouseGridPos();
	inline static GameAreaObject* m_gameAreaObjects[GRID_WIDTH][GRID_HEIGHT];

public:
	MouseHoleEntry* m_holeEntry;
	GameAreaObject m_holeExit{ 1, GRID_WIDTH - 1, GRID_HEIGHT, 0, 0, true };
	int mouseHoleSpriteIDs[4]{};
	GridPos m_lastSelected{ -1,-1 };
	GameArea();
	void Update();
	void PlaceObject(const FloatingObject& obj);
	FloatingObject GetObject();
	void DrawGameArea();
	void SetGameAreaObjects(GameAreaObject* gameAreaObjects[GRID_WIDTH][GRID_HEIGHT]);
	static GameAreaObject* GetGameAreaObject(GridPos pos);

	static Point2f GameToWorld(Point2f pos);
	static GridPos WorldToGame(Point2f pos);

	static GameAreaObject* GetObjectAtGridPosition(int x, int y);
	static void RotateEntryDirections(uint8_t& entryDirections);

	friend class Debug;
	friend class LevelLoader;
	static void ValidateEntryDirections(GameAreaObject& ga_obj);
	static std::array<bool, 4> GetBlockPossibleDirections(GameAreaObject& obj);
private:
	
public:
	static std::array<bool, 4> GetBlockValidDirections(GameAreaObject& obj);
};