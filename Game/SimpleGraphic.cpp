#include "Play.h"
#include "SimpleGraphic.h"

SimpleGraphic::SimpleGraphic(Play::Point2f pos, int spriteID)
{
	m_matrix = Play::MatrixIdentity();

	m_pos = pos;
	m_matrix.row[2] = { m_pos.x, m_pos.y, 1.f };
	m_spriteID = spriteID;
}

void SimpleGraphic::Draw()
{
	Play::DrawSpriteTransformed(m_spriteID, m_matrix, 0);
}