#include "Play.h"
#include "Time.h"
#include "TitleTextGraphic.h"
#include "EasingFunctions.h"

void TitleTextGraphic::Update()
{
	////////////////////////
	// Title Animation /////
	////////////////////////

	float transitionEndTime = 1.f;
	float t = Time::GetStateTime();
	double speed = 7;
	double squash = 40;

	if (t < transitionEndTime)
	{
		// SCALE
		// #TODO: Transition wouldn't line up properly with different values, but it works for now
		m_matrix.row[0].x = EaseOutElastic(t / 1.5f);
		m_matrix.row[1].y = EaseOutElastic(t / 1.5f);
	}
	else
	{
		// Ensures the top of the sine curve matches up with 1 ( as the ease out transition ends at 1 )
		double x = ((cos(t * speed)) / squash) + (1 - 1 / squash);
		double y = ((sin(t * speed)) / squash) + (1 - 1 / squash);

		m_matrix.row[0].x = static_cast<float>(x);
		m_matrix.row[1].y = static_cast<float>(y);
	}
}