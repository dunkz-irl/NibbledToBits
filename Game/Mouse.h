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

struct GridVector { 
	
	int x; int y; 

	friend bool operator==(GridVector rhs, GridVector lhs)
	{
		return (rhs.x == lhs.x) && (rhs.y == lhs.y);
	}
};

class Mouse : public GameObject
{
public:
	Mouse(Play::Point2f pos);

	void Update() override;
	void Draw() override;

private:
	void UpdateGridPosition();
	void UpdateTrackedGridSquares();
	void UpdateBehaviour();
	void UpdateRotation();
	void UpdateDirection();
	void ReverseDirection();
private:
	static std::vector<Mouse> m_vMice;
	const char* m_spriteNames[3]{ "mouseWhite", "mouseBlue", "mouseGrey" };
	GridVector m_currentDirection{ 0, 1 };
	GridVector m_currentPosition{ -2, -2 };
	GridVector m_nextPosition{ -2, -2 };

	float m_movementSpeed{ 1.f };

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
