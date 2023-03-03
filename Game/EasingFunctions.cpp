#include "Play.h"
#include "EasingFunctions.h"

// #CREDIT: easings.net
float EaseOutElastic(float x)
{
	const float c4 = (2.f * PLAY_PI) / 3.f;

	return x == 0.f
		? 0.f
		: x == 1.f
		? 1.f
		: pow(2.f, -10.f * x) * sin((x * 10.f - 0.75f) * c4) + 1.f;
}