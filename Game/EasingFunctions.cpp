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

float EastOutBounce(float start, float end, float t)
{
	float n1 = 7.5625;
	float d1 = 2.75;

	if (t < 1 / d1) 
	{
		t = n1 * t * t;
	}

	else if (t < 2 / d1) 
	{
	  t = n1 * (t -= 1.5f / d1) * t + 0.75f;
	}

	else if (t < 2.5 / d1) 
	{
	  t = n1 * (t -= 2.25f / d1) * t + 0.9375f;
	}

	else 
	{
	  t = n1 * (t -= 2.625f / d1) * t + 0.984375f;
	}

	return (start + (end - start) * t);

}

float EaseInOutQuint(float start, float end, float t)
{

	t =  t < 0.5f ? 16.f * t * t * t * t * t : 1.f - powf(-2.f * t + 2.f, 5.f) / 2.f;
	
	//return t;
	return (start + (end - start) * t);
}
