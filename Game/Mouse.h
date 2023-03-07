#pragma once
#include "GameObject.h"

struct GameAreaObject;

class Mouse : public GameObject
{
public:
	Mouse(Play::Point2f pos);

	void Update() override;
	void Draw() override;

private:
	void UpdateCurrentGridPos();

private:
	static std::vector<Mouse> m_vMice;
	const char* m_spriteNames[3]{ "mouseWhite", "mouseBlue", "mouseGrey" };
	Play::Vector2D m_currentDirection{ 0.f, 1.f };
	float m_movementSpeed{ 1.f };

	int m_gridPosX{ -2 };
	int m_gridPosY{ -2 };
	GameAreaObject* m_currentGridObj{ nullptr };
	GameAreaObject* m_nextGridObj{ nullptr };

};
