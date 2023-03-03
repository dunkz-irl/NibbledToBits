#pragma once
#include "GameObject.h"

class Mouse : public GameObject
{
public:
	Mouse(Play::Point2f pos);

	void Update() override;
	void Draw() override;

};

