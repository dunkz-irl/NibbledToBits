#pragma once
class Debug
{
public:
	static void DrawBoldText(std::string text, Play::Point2f pos);
	inline static bool s_active{ true };
};

