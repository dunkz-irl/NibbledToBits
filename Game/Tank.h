#pragma once
#include "GameArea.h"

class Tank : public GameAreaObject
{
public:
	void Update() override;
	void Draw() override;

	void Fire();
private:
	const char* m_turretSprite{ "tank_turret" };
	const char* m_crosshairSprite{ "crosshair" };
	int m_ammunition[5]{-1, -1, -1, -1, -1}; // ammo, with ga_obj id as type when picked up
	float m_bulletVelocity{ 2.5f };
	Play::Vector2D m_tankToCursorVec{ 0.f,0.f };
	Play::Point2D m_mousePos{ 0.f,0.f };
	Play::Point2D m_worldPos;
};

