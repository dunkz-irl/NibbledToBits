#pragma once
#include "GameObject.h"

struct GameAreaObject;
enum class GridDirection;
struct GridVector;

class Mouse : public GameObject
{
public:
	Mouse(Play::Point2f pos);

	void Update() override;
	void Draw() override;

	void ReverseDirection();
	void UpdateTrackedGridSquares();

	GridVector GetNextPosition() const { return m_nextPosition; }

	friend struct RotatingBlock;

private:
	void UpdateGridPosition();
	void UpdateBehaviour();
	void UpdateRotation();
	void UpdateDirection();
	bool CheckBlockForValidEntrance(const GameAreaObject& gameAreaObj);
	GridDirection GetCurrentDirectionEnum();
private:
	bool m_enteredNewSquare = false;
	static std::vector<Mouse> m_vMice;
	const char* m_spriteNames[3]{ "mouseWhite", "mouseBlue", "mouseGrey" };
	GridVector m_currentDirection{ 0, 1 };
	GridVector m_nextPosition{ -2, -2 };

	void SetNextPosition(GridVector val) { m_nextPosition = val; }
	float m_movementSpeed{ 1.f };

	GameAreaObject* m_currentGridObj;
	GameAreaObject* m_nextGridObj;

	// Maps onto enum class MouseDirection
	GridVector m_directionVectors[4]
	{
		{0, 1},
		{1, 0},
		{0, -1},
		{-1, 0}
	};
};
