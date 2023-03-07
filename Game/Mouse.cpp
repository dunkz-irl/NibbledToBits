#include "Play.h"
#include "GameArea.h"
#include "Mouse.h"

#include "Common.h"
#include "Debug.h"
#include "GameManager.h"

Mouse::Mouse(Play::Point2f pos) : GameObject::GameObject(GameObjectType::TYPE_MOUSE)
{	
	UpdateTrackedGridSquares();


	m_matrix.row[2].x = pos.x;
	m_matrix.row[2].y = pos.y;

	// Flip the sprite on the x axis occasionally for subtle variety
	if (Play::RandomRollRange(0, 1))
	{
		m_matrix = m_matrix * Play::MatrixScale(-1.f, 1.f);
	}

	m_animSpeed = 19.f + Play::RandomRollRange(-100, 100) / 100.f;
	m_animFrame = Play::RandomRoll(8) - 1; // #TODO: Assumes there will always be 8 frames which might not be true of other animation states

	m_movementSpeed = 3.2f;

	// Set sprite to one of three
	m_spriteID = Play::GetSpriteId(m_spriteNames[Play::RandomRoll(3) - 1]);	
}

void Mouse::Update()
{
	UpdateAnimation();

	UpdateGridPosition();
	
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
		Point2f currentSquareWorldPos = GameArea::GameToWorld({ m_currentPosition.x, m_currentPosition.y });
		Play::Graphics::DrawRect(currentSquareWorldPos - Play::Vector2f{ SQUARE_SIZE / 2.f, SQUARE_SIZE / 2.f }, currentSquareWorldPos + Play::Vector2f{ SQUARE_SIZE / 2.f, SQUARE_SIZE / 2.f }, Play::PIX_BLUE);

		// Draw next grid square
		Point2f nextSquareWorldPos = GameArea::GameToWorld({ m_currentPosition.x + m_currentDirection.x, m_currentPosition.y + m_currentDirection.y });
		Play::Graphics::DrawRect(nextSquareWorldPos - Play::Vector2f{ SQUARE_SIZE / 2.f, SQUARE_SIZE / 2.f }, nextSquareWorldPos + Play::Vector2f{ SQUARE_SIZE / 2.f, SQUARE_SIZE / 2.f }, Play::PIX_MAGENTA);

		Debug::DrawBoldText("This: " + std::to_string(m_currentGridObj->id), currentSquareWorldPos + Point2f{ SQUARE_SIZE, 0.f });
		Debug::DrawBoldText("Next: " + std::to_string(m_nextGridObj->id), nextSquareWorldPos + Point2f{ SQUARE_SIZE, 0.f });

	}

	std::string debugText = "{ " + std::to_string(m_currentPosition.x) + ", " + std::to_string(m_currentPosition.y) + " }";
	Debug::DrawBoldText(debugText, m_matrix.row[2]);
}

void Mouse::UpdateGridPosition()
{
	// #TODO: Could combine GridVector and GridPos maybe? Bit confusing
	GridPos gridPos = GameArea::WorldToGame({ m_matrix.row[2].x, m_matrix.row[2].y });

	m_currentPosition = { gridPos.x, gridPos.y };
	m_nextPosition = { gridPos.x + m_currentDirection.x, gridPos.y + m_currentDirection.y };
}

void Mouse::UpdateTrackedGridSquares()
{
	m_currentGridObj = &GameArea::GetGameAreaObject({ m_currentPosition.x, m_currentPosition.y });
	m_nextGridObj = &GameArea::GetGameAreaObject({ m_currentPosition.x + m_currentDirection.x, m_currentPosition.y + m_currentDirection.y });
}

void Mouse::UpdateBehaviour()
{
	// Single wall
	if (m_nextGridObj->id == 4)
	{
		ReverseDirection();
	}

	// Check for entrance mouse hole
	GameAreaObject* pEntryObj = GM_INST.GetEntryObj();
	if (m_nextPosition.x == pEntryObj->posx && m_nextPosition.y == pEntryObj->posy)
	{
		ReverseDirection();
	}
}

void Mouse::UpdateRotation()
{
	Matrix2D rotMatrix;

	if (m_currentDirection == GridVector{ 0, 1 }) // Up
		rotMatrix = MatrixRotation(0);
	else if (m_currentDirection == GridVector{ 1, 0 }) // Right
		rotMatrix = MatrixRotation(PLAY_PI * 0.5f);
	else if (m_currentDirection == GridVector{ 0, -1 }) // Down
		rotMatrix = MatrixRotation(PLAY_PI);
	else if (m_currentDirection == GridVector{ -1, 0 }) // Left
		rotMatrix = MatrixRotation(PLAY_PI * 1.5f);

	m_matrix.row[0] = rotMatrix.row[0];
	m_matrix.row[1] = rotMatrix.row[1];
}

void Mouse::UpdateDirection()
{
	m_velocity = Vector2f{ m_currentDirection.x, m_currentDirection.y };
}

void Mouse::ReverseDirection()
{
	m_currentDirection = {m_currentDirection.x * -1, m_currentDirection.y * -1};
}
