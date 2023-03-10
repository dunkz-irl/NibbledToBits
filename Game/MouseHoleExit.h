#pragma once
#include "GameArea.h"

class MouseHoleExit : public GameAreaObject
{
	using GameAreaObject::GameAreaObject;
public:
	void OnCurrentSquare(void* pObj) override;
};

