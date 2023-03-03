#pragma once

#include "GameObject.h"

class GameObjectFactory
{
public:
	static GameObject* Create(GameObjectType type, Play::Point2f pos);
};
