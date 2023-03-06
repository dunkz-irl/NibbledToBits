#include "Play.h"
#include "EasingFunctions.h"
#include "Time.h"

#include "MouseGraphic.h"

void MouseGraphic::Update()
{
	float t = Time::GetAppStateTime() * 2.f;

	Play::Matrix2D rotMatrix = Play::MatrixRotation(sin(t) / 4.f);

	m_matrix.row[0] = rotMatrix.row[0]; // Rotation
	m_matrix.row[1] = rotMatrix.row[1]; // Rotation

	m_matrix.row[1].y *= EaseOutElastic(t * 1.2f); // Vertical squish

	m_matrix.row[2].y = m_pos.y * EaseOutElastic(t / 4.f); // Vertical movement
	m_matrix.row[2].x = m_pos.x + (cos(t) * 10.f);
}