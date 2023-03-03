#pragma once
class IApplicationState
{
public:
	~IApplicationState() = default;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual IApplicationState* OnUpdate() = 0;
	virtual void OnDraw() = 0;

	std::string GetStateName()
	{
		if (m_debugStateName == "")
		{
			PLAY_ASSERT_MSG(false, "No Application State Name set");
		}

		return m_debugStateName;
	}

	static float GetStateTime() { return m_stateTime; };

	friend class ApplicationManager;

protected:
	std::string m_debugStateName{ "" };
	static inline float m_stateTime{ 0.f }; // #TODO: I have no idea what inline means, but it lets this be static
};


