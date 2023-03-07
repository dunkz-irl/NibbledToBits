#include "Play.h"
#include "GameArea.h"
#include "Mouse.h"

#include "Common.h"
#include "Debug.h"

Mouse::Mouse(Play::Point2f pos) : GameObject::GameObject(GameObjectType::TYPE_MOUSE)
{
	m_matrix.row[2].x = pos.x;
	m_matrix.row[2].y = pos.y;

	// Flip the sprite on the x axis occasionally for subtle variety
	if (Play::RandomRollRange(0, 1))
	{
		m_matrix = m_matrix * Play::MatrixScale(-1.f, 1.f);
	}

	m_animSpeed = 19.f + Play::RandomRollRange(-100, 100) / 100.f;
	m_animFrame = Play::RandomRoll(8) - 1; // #TODO: Assumes there will always be 8 frames which might not be true of other animation states

	m_movementSpeed = 0.6f;

	// Set sprite to one of three
	m_spriteID = Play::GetSpriteId(m_spriteNames[Play::RandomRoll(3) - 1]);	
}

void Mouse::Update()
{
	UpdateAnimation();

	UpdateCurrentGridPos();

	// Update current and next grid object

	m_velocity = m_currentDirection * m_movementSpeed;

	m_matrix.row[2] += m_velocity;
}

void Mouse::Draw()
{
	Play::DrawSpriteTransformed(m_spriteID, m_matrix, m_animFrame);

	std::string debugText = "{ " + std::to_string(m_gridPosX) + ", " + std::to_string(m_gridPosY) + " }";
	Debug::DrawBoldText(debugText, m_matrix.row[2]);
}

void Mouse::UpdateCurrentGridPos()
{
	GridPos gridPos = GameArea::WorldToGame({ m_matrix.row[2].x, m_matrix.row[2].y });

	m_gridPosX = gridPos.x;
	m_gridPosY = gridPos.y;
}
