#include "Play.h"
#include "Mouse.h"

Mouse::Mouse(Play::Point2f pos)
{
	m_matrix.row[2].x = pos.x;
	m_matrix.row[2].y = pos.y;

	m_animSpeed = 19.f;
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
