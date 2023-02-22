#pragma once

extern int DISPLAY_WIDTH;
extern int DISPLAY_HEIGHT;

#define CENTRE_POINT {DISPLAY_WIDTH / 2.f, DISPLAY_HEIGHT / 2.f}
#define DEBUG_TEXT(x) std::to_string(x).c_str()