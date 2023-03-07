#include "Play.h"
#include "Mouse.h"

Mouse::Mouse(Play::Point2f pos) : GameObject::GameObject(GameObjectType::TYPE_MOUSE)
{
	m_matrix.row[2].x = pos.x;
	m_matrix.row[2].y = pos.y;

	m_animSpeed = 19.f + Play::RandomRollRange(-100, 100) / 100.f;
	m_animFrame = Play::RandomRoll(8) - 1; // #TODO: Assumes there will always be 8 frames which might not be true of other animation states

	m_movementSpeed = 2.f;

	// Set sprite to one of three
	m_spriteID = Play::GetSpriteId(m_spriteNames[Play::RandomRoll(3) - 1]);	
}

void Mouse::Update()
{
	UpdateAnimation();

	m_velocity = m_currentDirection * m_movementSpeed;

	m_matrix.row[2] += m_velocity;
}

void Mouse::Draw()
{
	Play::DrawSpriteTransformed(m_spriteID, m_matrix, m_animFrame);
}
