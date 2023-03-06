#include "Play.h"
#include "EasingFunctions.h"
#include "Time.h"

#include "MouseGraphic.h"

void MouseGraphic::Update()
{
	float t = Time::GetAppStateTime();

	m_matrix.row[2].y = m_pos.y * EaseOutElastic(t / 4.f);
	m_matrix.row[1].y = EaseOutElastic(t * 1.2f);

	m_matrix = m_matrix * Play::MatrixRotation(sin(t) / 400.f);
}