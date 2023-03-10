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

	GameAreaObject(int id = -1, int posx = 0, int posy = 0, int rot = 0, int misc = 0, bool mouseHole = false);
	virtual ~GameAreaObject() = default;

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

	virtual void Update() { };
	virtual void OnCurrentSquare(void* pObj) { };
	virtual void OnNextSquare(void* pObj) { };
	virtual void Reset() { };

	Play::Matrix2D m_matrix{ Play::MatrixIdentity() };
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
class MouseHoleExit;

class GameArea {

public:
	GameArea();
	~GameArea();

	void Update();
	void PlaceObject(const FloatingObject& obj);
	void DrawGameArea();
	void SetGameAreaObjects(GameAreaObject* gameAreaObjects[GRID_WIDTH][GRID_HEIGHT]);

	static void ValidateEntryDirections(GameAreaObject& ga_obj);
	static void RotateEntryDirections(uint8_t& entryDirections);

	static std::array<bool, 4> GetBlockPossibleDirections(GameAreaObject& obj);
	static std::array<bool, 4> GetBlockValidDirections(GameAreaObject& obj);
	static GameAreaObject* GetGameAreaObject(GridPos pos);
	static GameAreaObject* GetObjectAtGridPosition(int x, int y);
	FloatingObject GetObject();

	static Point2f GameToWorld(Point2f pos);
	static GridPos WorldToGame(Point2f pos);

public:
	int mouseHoleSpriteIDs[4]{};
	MouseHoleEntry* m_holeEntry;
	MouseHoleExit* m_holeExit;
	GridPos m_lastSelected{ -1,-1 };

	friend class Debug;
	friend class LevelLoader;
	friend class GoState;

private:
	GridPos GetMouseGridPos();
	inline static GameAreaObject* m_gameAreaObjects[GRID_WIDTH][GRID_HEIGHT];
};