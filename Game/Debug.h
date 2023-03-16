#pragma once
class Debug
{
public:
	static void DrawBoldText(std::string text, Play::Point2f pos);
	static void DrawGameAreaObjectDebugInfo();
	inline static bool s_active{ false };
};

