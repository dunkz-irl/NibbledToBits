#pragma once
#include "GameArea.h"

class AmmoPickup : public GameAreaObject
{

public:
	void OnCurrentSquare(void* pObj) override;
	void Reset() override;

private:
	bool m_active{ true };
};

