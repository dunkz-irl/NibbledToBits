#include "Play.h"
#include "ParticlesCommon.h"

// From https://stackoverflow.com/questions/5289613/generate-random-float-between-two-floats
float RandomFloat(float min, float max)
{
	float random = (static_cast<float>(rand())) / static_cast<float>(RAND_MAX);
	float diff = max - min;
	float r = random * diff;
	return min + r;
}

float DegToRads(float a)
{
	float result = a * (PI / 180.f);
	return result;
}

Play::Vector2f RotateVector(Play::Vector2f vector, float angle)
{
	return { vector.x * cos(angle) - vector.y * sin(angle), vector.x * sin(angle) + vector.y * cos(angle) };
}


float Magnitude(Play::Vector2f a)
{
	return sqrtf(pow(a.x, 2.f) + pow(a.y, 2.f));
}

Play::Vector2f NormaliseVector(Play::Vector2f vector)
{
	return vector / Magnitude(vector);
}

float AngleBetweenTwoVectors(Play::Vector2f a, Play::Vector2f b)
{
	return atan2(b.y, b.x) - atan2(a.y, a.x);
}