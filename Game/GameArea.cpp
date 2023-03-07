#include "Play.h"
#include "GameArea.h"
#include "GameManager.h"

using namespace Play;

float PI{ 3.14159265358979323846f };
int GAME_AREA_WIDTH{ 870 };
int GAME_AREA_HEIGHT{ 720 };
int SQUARE_SIZE{ 50 };
int BOARDER_PIXELS{ 35 };

GameArea::GameArea() {
	//Get sprite ID's for each mouse hole rotated sprite
	mouseHoleSpriteIDs[0] = Play::GetSpriteId("mouse_hole_top");
	mouseHoleSpriteIDs[1] = Play::GetSpriteId("mouse_hole_left");
	mouseHoleSpriteIDs[2] = Play::GetSpriteId("mouse_hole_bottom");
	mouseHoleSpriteIDs[3] = Play::GetSpriteId("mouse_hole_right");
}

void GameArea::Update() {
	// #Duncan Don't want players to be able to do this
	//
	//Increase and decrease the misc variable of the last selected object when up and down arrors are pressed
	/*
	if (m_lastSelected.x != -1 && m_lastSelected.y != -1) {
		if (Play::KeyPressed(VK_UP)) {
			GameAreaObject& gameAreaObject = GetGameAreaObject(m_lastSelected);
			gameAreaObject.misc += 1;
		}
		if (Play::KeyPressed(VK_DOWN)) {
			GameAreaObject& gameAreaObject = GetGameAreaObject(m_lastSelected);
			gameAreaObject.misc -= 1;
		}
	}
	*/

	//Rotate object if the right mouse button is pressed
	if (Play::KeyPressed(VK_RBUTTON)) {
		GridPos mouseGridPos = GetMouseGridPos();
		if (mouseGridPos.x < 0 || mouseGridPos.y < 0 || mouseGridPos.x > GRID_WIDTH || mouseGridPos.y > GRID_HEIGHT) {
			return;
		}

		GameAreaObject& ga_obj = GetGameAreaObject(mouseGridPos);

		if (ga_obj.rotatable)
		{
			int& rotation = ga_obj.rot;
			rotation += 1;
			if (rotation > 3) {
				rotation = 0;
			}
		}
	}
}

void GameArea::DrawGameArea() {
	// Draw each item in the grid if it has a valid id
	for (int i = 0; i < GRID_WIDTH; ++i) {
		for (int j = 0; j < GRID_HEIGHT; ++j) {
			const GameAreaObject& obj = m_gameAreaObjects[i][j];
			if (obj.id != -1) {
				const Play::Point2D worldPos = GameToWorld({ obj.posx, obj.posy });
				Play::DrawSprite(GetSpriteIDFromObjectID(obj.id, obj.rot), worldPos, 0);
			}
		}
	}
	// Draw the correct mouse hole sprite and the E and X text
	const auto drawHole = [this](const GameAreaObject& hole, char letter) {
		if (hole.vis) {
			const int IDIndex = (hole.posy == GRID_HEIGHT ? 0 : hole.posx == -1 ? 1 : hole.posy == -1 ? 2 : hole.posx == GRID_WIDTH ? 3 : 0);
			const Play::Point2D worldPos = GameToWorld({ hole.posx, hole.posy });
			Play::DrawSprite(mouseHoleSpriteIDs[IDIndex], worldPos, 0);
			const Play::Point2D textPos = worldPos + Play::Point2D{ 0, hole.posy == GRID_HEIGHT ? -SQUARE_SIZE : SQUARE_SIZE };
			Play::DrawFontText("fontui64px", std::string(1, letter), textPos, Play::CENTRE);
		}
	};
	drawHole(m_holeEntry, 'E');
	drawHole(m_holeExit, 'X');

	// Draw the misc variable above the last selected object
	if (m_lastSelected.x != -1 && m_lastSelected.y != -1) {
		const GameAreaObject& lastSelectedObject = GetGameAreaObject(m_lastSelected);
		const Play::Point2D worldPos = GameToWorld({ m_lastSelected.x, m_lastSelected.y });
		const Play::Point2D textPos = worldPos + Play::Point2D{ 0, SQUARE_SIZE };
		// Play::DrawFontText("fontui64px", std::to_string(lastSelectedObject.misc), textPos, Play::CENTRE);
	}
}


Point2f GameArea::GameToWorld(Point2f pos) {
	pos.x = pos.x * static_cast<float>(SQUARE_SIZE) + static_cast<float>(SQUARE_SIZE) / 2.f;
	pos.y = pos.y * static_cast<float>(SQUARE_SIZE) + static_cast<float>(SQUARE_SIZE) / 2.f;
	Point2f botLeftGrid{ DISPLAY_WIDTH - GAME_AREA_WIDTH + BOARDER_PIXELS, DISPLAY_HEIGHT - GAME_AREA_HEIGHT + BOARDER_PIXELS };
	return pos + botLeftGrid;
}

GridPos GameArea::WorldToGame(Point2f pos) {
	Point2f botLeftGrid{ DISPLAY_WIDTH - GAME_AREA_WIDTH + BOARDER_PIXELS, DISPLAY_HEIGHT - GAME_AREA_HEIGHT + BOARDER_PIXELS };
	pos.x -= abs(((int)pos.x) % SQUARE_SIZE);
	pos.y -= abs(((int)pos.y) % SQUARE_SIZE);
	pos -= botLeftGrid;

	return{ pos.x >= 0 ? int(pos.x / SQUARE_SIZE) : int(pos.x / SQUARE_SIZE) - 1, pos.y >= 0 ? int(pos.y / SQUARE_SIZE) : int(pos.y / SQUARE_SIZE) - 1 };
}

GameAreaObject* GameArea::GetObjectAtGridPosition(int x, int y)
{
	GameAreaObject& obj = GM_INST.m_gameArea->GetGameAreaObject({x, y});
	if (obj.id != -1)
	{
		return &obj;
	}

	return nullptr;
}

void GameArea::PlaceObject(const FloatingObject& obj) {
	const GridPos mouseGridPos = GetMouseGridPos();

	// Place a mouse hole object, which can't be removed and will snap to the closest valid location
	if (obj.mouseHole) {
		int x = std::clamp(mouseGridPos.x, -1, GRID_WIDTH);
		int y = std::clamp(mouseGridPos.y, -1, GRID_HEIGHT);

		const int distToLeft = std::abs(-1 - x);
		const int distToRight = std::abs(GRID_WIDTH - x);
		const int distToDown = std::abs(-1 - y);
		const int distToUp = std::abs(GRID_HEIGHT - y);

		if (std::min(distToLeft, distToRight) < std::min(distToDown, distToUp)) {
			x = (distToLeft > distToRight) ? GRID_WIDTH : -1;
		}
		else {
			y = (distToDown > distToUp) ? GRID_HEIGHT : -1;
		}

		if (x == -1 || x == GRID_WIDTH) {
			y = std::clamp(y, 0, GRID_HEIGHT - 1);
		}

		GameAreaObject& hole = (obj.id == 0) ? m_holeEntry : m_holeExit;
		hole.posx = x;
		hole.posy = y;
		hole.vis = true;

		return;
	}

	// Check if the object has been dropped within the game area
	if (mouseGridPos.x < 0 || mouseGridPos.y < 0 || mouseGridPos.x >= GRID_WIDTH || mouseGridPos.y >= GRID_HEIGHT) {
		return;
	}

	// Set the object at the mouse location to be the held item
	auto& tmpGameAreaObject = m_gameAreaObjects[mouseGridPos.x][mouseGridPos.y];
	tmpGameAreaObject.id = obj.id;
	tmpGameAreaObject.rot = obj.rot;
	tmpGameAreaObject.misc = obj.misc;
	tmpGameAreaObject.posx = mouseGridPos.x;
	tmpGameAreaObject.posy = mouseGridPos.y;
	m_lastSelected = mouseGridPos;
}

FloatingObject GameArea::GetObject() {
	GridPos mouseGridPos = GetMouseGridPos();
	// #Duncan Player shouldn't be able to move entrance and exit
	//
	/*
	//Return a mouse hole object
	if (mouseGridPos.x == m_holeEntry.posx && mouseGridPos.y == m_holeEntry.posy) {
		m_holeEntry.vis = false;
		m_lastSelected = { -1, -1 };
		return { m_holeEntry.id, 0, 0, true };
	}
	if (mouseGridPos.x == m_holeExit.posx && mouseGridPos.y == m_holeExit.posy) {
		m_holeExit.vis = false;
		m_lastSelected = { -1, -1 };
		return { m_holeExit.id, 0, 0, true };
	}
	*/

	if (mouseGridPos.x < 0 || mouseGridPos.y < 0 || mouseGridPos.x >= GRID_WIDTH || mouseGridPos.y >= GRID_HEIGHT) {
		return { -1, 0 };
	}

	//If within the game area and the grid location contains a valid object return it
	GameAreaObject tmpGameAreaObject = m_gameAreaObjects[mouseGridPos.x][mouseGridPos.y];
	if (!tmpGameAreaObject.pickupable)
	{
		return { -1, 0 };
	}

	m_gameAreaObjects[mouseGridPos.x][mouseGridPos.y].id = -1;

	if (tmpGameAreaObject.id != -1) {
		m_lastSelected = { -1, -1 };
	}

	return { tmpGameAreaObject.id, tmpGameAreaObject.rot, tmpGameAreaObject.misc };
}

GridPos GameArea::GetMouseGridPos() {
	Point2f mouseWorldPos = Play::GetMousePos();
	GridPos mouseSnapPos = WorldToGame(mouseWorldPos);

	return mouseSnapPos;
}

void GameArea::SetGameAreaObjects(GameAreaObject gameAreaObjects[GRID_WIDTH][GRID_HEIGHT]) {
	std::memcpy(m_gameAreaObjects, gameAreaObjects, sizeof(GameAreaObject) * GRID_WIDTH * GRID_HEIGHT);
}

GameAreaObject& GameArea::GetGameAreaObject(GridPos pos) {
	return m_gameAreaObjects[pos.x][pos.y];
}