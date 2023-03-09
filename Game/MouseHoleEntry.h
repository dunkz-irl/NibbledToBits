#pragma once
#include "GameArea.h"

class MouseHoleEntry : public GameAreaObject
{
	using GameAreaObject::GameAreaObject;
public:
	
	void OnCurrentSquare(void* pObj) override;
	void OnNextSquare(void* pObj) override;
};
