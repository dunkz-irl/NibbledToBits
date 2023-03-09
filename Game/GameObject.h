#pragma once

struct GridVector;

enum class GameObjectType
{
	TYPE_MOUSE = 0,
	TYPE_DESTROYED,
	TYPE_CLEANUP,
	COUNT,
};

class GameObject
{
public:
	int GetID();
	GameObject(GameObjectType type);

	virtual void Update() = 0;
	virtual void UpdateDestroyed();
	virtual void Draw() = 0;

	void UpdateAnimation();

	// Getters
	GameObjectType GetGameObjectType();
	GridVector GetGridPosition();

protected:
	int m_spriteID{ -1 };
	int m_drawLayer{ -1 };
	int m_animFrame{ 0 };
	float m_animSpeed{ 1.f };
	float m_frameTimer{ 0.f };
	float m_opacity{ 1.f };
	Play::Matrix2D m_matrix{ Play::MatrixIdentity() };
	Play::Vector2D m_velocity{ 0.f,0.f };
	GameObjectType m_type{ GameObjectType::COUNT };
	GridVector m_currentPosition{ -2, -2 };

private:
	int m_id{ -1 };

};

