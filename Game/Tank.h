#pragma once
#include "GameArea.h"

class Tank : public GameAreaObject
{
public:
	void Update() override;
	void Draw() override;

	static void AddAmmo(int id);
	static int UseAmmo();

	void Fire(int bulletSpriteID);
private:
	const char* m_turretSprite{ "tank_turret" };
	const char* m_crosshairSprite{ "crosshair" };
	static inline std::queue<int> m_ammunition { }; // ammo, with ga_obj id as type when picked up
	float m_bulletVelocity{ 5.5f };
	Play::Vector2D m_tankToCursorVec{ 0.f,0.f };
	Play::Point2D m_mousePos{ 0.f,0.f };
	Play::Point2D m_worldPos;
};

