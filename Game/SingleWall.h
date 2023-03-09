#pragma once
#include "GameArea.h"

class SingleWall : public GameAreaObject
{

public:
	void OnCurrentSquare(void* pObj) override;
	void OnNextSquare(void* pObj) override;

};
