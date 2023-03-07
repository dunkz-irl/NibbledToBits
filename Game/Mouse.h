#pragma once
#include "GameObject.h"

struct GameAreaObject;

enum class MouseDirection
{
	UP = 0,
	DOWN,
	LEFT,
	RIGHT
};

class Mouse : public GameObject
{
public:
	Mouse(Play::Point2f pos);

	void Update() override;
	void Draw() override;

private:
	void UpdateCurrentGridPos();

	void UpdateTrackedGridSquares();
	void UpdateBehaviour();
	void UpdateRotation();
	void UpdateDirection();
	void ReverseDirection();
	int m_nextSquareX;
	int m_nextSquareY;
private:
	static std::vector<Mouse> m_vMice;
	const char* m_spriteNames[3]{ "mouseWhite", "mouseBlue", "mouseGrey" };
	MouseDirection m_currentDirection{ MouseDirection::UP };
	float m_movementSpeed{ 1.f };

	int m_gridPosX{ -2 };
	int m_gridPosY{ -2 };
	GameAreaObject* m_currentGridObj{ nullptr };
	GameAreaObject* m_nextGridObj{ nullptr };

	// Maps onto enum class MouseDirection
	Play::Vector2f m_directionVectors[4]
	{
		{0.f, 1.f},
		{0.f, -1.f},
		{-1.f, 0.f},
		{1.f, 0.f}
	};
};
