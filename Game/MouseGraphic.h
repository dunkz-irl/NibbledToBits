#pragma once
#include "SimpleGraphic.h"

class MouseGraphic : public SimpleGraphic
{
	using SimpleGraphic::SimpleGraphic; // #NOTE: Apparently this inherits all constructors?
public:
	void Update();
};
