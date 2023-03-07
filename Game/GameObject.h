#pragma once

enum class GameObjectType
{
	TYPE_MOUSE = 0,
	TYPE_DESTROYED,
	COUNT,
};

class GameObject
{
public:
	GameObject();
	int GetID();

	virtual void Update() = 0;
	virtual void UpdateDestroyed();

	virtual void Draw() = 0;

	void UpdateAnimation();

	// Getters
	GameObjectType GetGameObjectType();

protected:
	int m_spriteID{ -1 };
	int m_drawLayer{ -1 };
	int m_animFrame{ 0 };
	float m_animSpeed{ 1.f };
	float m_frameTimer{ 0.f };

	Play::Matrix2D m_matrix{ Play::MatrixIdentity() };

	Play::Vector2D m_velocity{ 0.f,0.f };

private:
	int m_id{ -1 };
	GameObjectType m_type;
};

