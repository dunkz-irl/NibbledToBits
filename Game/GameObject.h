#pragma once

enum class GameObjectType
{
	TYPE_MOUSE = 0,
	COUNT,
};

class GameObject
{
public:
	GameObject();
	int GetID();

	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	int m_spriteID{ -1 };
	int m_drawLayer{ -1 };
	Play::Point2f m_pos{ -1.f,-1.f };
	float m_rot{ -1.f };

private:
	int m_id{ -1 };
};

