#pragma once
#include "IGameState.h"

class ApplicationManager
{

public:
	
	// Singleton	//
	static ApplicationManager& Instance();
	static void Destroy();
	//		//		//

	void Update();
	void Draw();

private:

	// Singleton	//
	ApplicationManager();
	~ApplicationManager();
	static ApplicationManager* s_pInstance;

	ApplicationManager& operator=(const ApplicationManager) = delete;
	ApplicationManager(const ApplicationManager&) = delete;
	//		//		//

	IGameState* m_pGameState;

};

