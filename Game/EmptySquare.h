#pragma once
#include "GameArea.h"

class EmptySquare : public GameAreaObject
{
	void OnCurrentSquare(void* pObj) override;
};

