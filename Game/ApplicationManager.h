#pragma once
#include "IApplicationState.h"

class ApplicationManager
{

public:
	
	// Singleton	//
	static ApplicationManager& Instance();
	static void Destroy();
	//		//		//

	void Update(float elapsedTime);
	void Draw();

	bool m_DebugMode{ true };
	friend class Time;

private:

	// Singleton	//
	ApplicationManager();
	~ApplicationManager();
	static ApplicationManager* s_pInstance;

	ApplicationManager& operator=(const ApplicationManager) = delete;
	ApplicationManager(const ApplicationManager&) = delete;
	//		//		//

	IApplicationState* m_pGameState;
};

