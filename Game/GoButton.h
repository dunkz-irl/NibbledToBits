#pragma once
#include "Button.h"

class GoButton : public Button
{
	using Button::Button;

public:
	void Update() override;
};

