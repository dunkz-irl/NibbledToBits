#pragma once
#include "GameArea.h"

struct RotatingBlock : public GameAreaObject
{
	virtual void OnCurrentSquare(void* pMouse) override;
	virtual void OnNextSquare(void* pMouse) override;
};
