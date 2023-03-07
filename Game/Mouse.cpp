#include "Play.h"
#include "GameArea.h"
#include "Mouse.h"

#include "Common.h"
#include "Debug.h"
#include "GameManager.h"

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

	m_movementSpeed = 0.7f;

	// Set sprite to one of three
	m_spriteID = Play::GetSpriteId(m_spriteNames[Play::RandomRoll(3) - 1]);	
}

void Mouse::Update()
{
	UpdateAnimation();

	UpdateCurrentGridPos();
	
	UpdateTrackedGridSquares(); // Update current and next grid object

	UpdateBehaviour(); // Changes based on next grid square.

	UpdateDirection();

	UpdateRotation();


	
	m_velocity *= m_movementSpeed;

	m_matrix.row[2] += m_velocity;
}

void Mouse::Draw()
{
	

	Play::DrawSpriteTransformed(m_spriteID, m_matrix, m_animFrame);

	if (Debug::s_active)
	{
		// Draw current grid square
		Point2f currentSquareWorldPos = GameArea::GameToWorld({m_gridPosX, m_gridPosY});
		Play::Graphics::DrawRect(currentSquareWorldPos - Play::Vector2f{ SQUARE_SIZE / 2.f, SQUARE_SIZE / 2.f }, currentSquareWorldPos + Play::Vector2f{ SQUARE_SIZE / 2.f, SQUARE_SIZE / 2.f }, Play::PIX_BLUE);

		// Draw next grid square
		Point2f nextSquareWorldPos = GameArea::GameToWorld({ m_nextSquareX, m_nextSquareY });
		Play::Graphics::DrawRect(nextSquareWorldPos - Play::Vector2f{ SQUARE_SIZE / 2.f, SQUARE_SIZE / 2.f }, nextSquareWorldPos + Play::Vector2f{ SQUARE_SIZE / 2.f, SQUARE_SIZE / 2.f }, Play::PIX_MAGENTA);

		Debug::DrawBoldText("This: " + std::to_string(m_currentGridObj->id), currentSquareWorldPos + Point2f{SQUARE_SIZE, 0.f});
		Debug::DrawBoldText("Next: " + std::to_string(m_nextGridObj->id), nextSquareWorldPos + Point2f{SQUARE_SIZE, 0.f});
	}

	std::string debugText = "{ " + std::to_string(m_gridPosX) + ", " + std::to_string(m_gridPosY) + " }";
	Debug::DrawBoldText(debugText, m_matrix.row[2]);
}

void Mouse::UpdateCurrentGridPos()
{
	GridPos gridPos = GameArea::WorldToGame({ m_matrix.row[2].x, m_matrix.row[2].y });

	m_gridPosX = gridPos.x;
	m_gridPosY = gridPos.y;
}

void Mouse::UpdateTrackedGridSquares()
{
	m_nextSquareX = m_gridPosX + static_cast<int>(m_directionVectors[(int)m_currentDirection].x);
	m_nextSquareY = m_gridPosY + static_cast<int>(m_directionVectors[(int)m_currentDirection].y);

	m_currentGridObj = &GameArea::GetGameAreaObject({ m_gridPosX, m_gridPosY });
	m_nextGridObj = &GameArea::GetGameAreaObject({ m_gridPosX + static_cast<int>(m_directionVectors[(int)m_currentDirection].x), m_gridPosY + static_cast<int>(m_directionVectors[(int)m_currentDirection].y) });
}

void Mouse::UpdateBehaviour()
{
	// Single wall
	if (m_nextGridObj->id == 4)
	{
		ReverseDirection();
	}

	if (m_nextSquareX == GM_INST.GetEntryObj()->posx && m_nextSquareY == GM_INST.GetEntryObj()->posy)
	{
		ReverseDirection();
	}
}

void Mouse::UpdateRotation()
{
	switch (m_currentDirection)
	{
	case MouseDirection::UP:
		m_matrix.row[0] = MatrixRotation(0).row[0];
		m_matrix.row[1] = MatrixRotation(0).row[1];
		break;
	case MouseDirection::DOWN:
		m_matrix.row[0] = MatrixRotation(PLAY_PI).row[0];
		m_matrix.row[1] = MatrixRotation(PLAY_PI).row[1];
		break;
	case MouseDirection::LEFT:
		m_matrix.row[0] = MatrixRotation(PLAY_PI * 1.5f).row[0];
		m_matrix.row[1] = MatrixRotation(PLAY_PI * 1.5f).row[1];
		break;
	case MouseDirection::RIGHT:
		m_matrix.row[0] = MatrixRotation(PLAY_PI * 0.5f).row[0];
		m_matrix.row[1] = MatrixRotation(PLAY_PI * 0.5f).row[1];
		break;
	default:
		break;
	}
}

void Mouse::UpdateDirection()
{
	switch (m_currentDirection)
	{
	case MouseDirection::UP:
		m_velocity = { 0.f, 1.f };
		break;
	case MouseDirection::DOWN:
		m_velocity = { 0.f, -1.f };
		break;
	case MouseDirection::LEFT:
		m_velocity = { -1.f, 0.f };
		break;
	case MouseDirection::RIGHT:
		m_velocity = { 21.f, 0.f };
		break;
	default:
		break;
	}
}

void Mouse::ReverseDirection()
{
	switch (m_currentDirection)
	{
	case MouseDirection::UP:
		m_currentDirection = MouseDirection::DOWN;
		break;
	case MouseDirection::DOWN:
		m_currentDirection = MouseDirection::UP;
		break;
	case MouseDirection::LEFT:
		m_currentDirection = MouseDirection::RIGHT;
		break;
	case MouseDirection::RIGHT:
		m_currentDirection = MouseDirection::LEFT;
		break;
	default:
		break;
	}
}
