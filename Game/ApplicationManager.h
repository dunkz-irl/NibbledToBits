#pragma once
#include "IGameState.h"

class ApplicationManager
{

private:
	IGameState* m_pGameState;

public:
	ApplicationManager();
	~ApplicationManager();

	void Update();
	void Draw();
};

