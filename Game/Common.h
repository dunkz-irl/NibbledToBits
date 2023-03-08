#pragma once

extern const int DISPLAY_WIDTH;
extern const int DISPLAY_HEIGHT;

#define CENTRE_POINT {DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f}
#define DEBUG_TEXT(x) std::to_string(x).c_str()

enum class GridDirection
{
	UP = 0,
	RIGHT,
	DOWN,
	LEFT
};

struct GridVector 
{
	int x; int y;

	friend bool operator==(GridVector rhs, GridVector lhs)
	{
		return (rhs.x == lhs.x) && (rhs.y == lhs.y);
	}
};

extern GridVector g_directionVectors[4];