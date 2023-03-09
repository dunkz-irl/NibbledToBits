#pragma once
template <typename T>
class Singleton
{
public:
	// Singleton	//
	static T& Instance();
	static void Destroy();
	//		//		//

protected:
	// Singleton	//
	Singleton<T>();
	~Singleton<T>();
	static inline T* s_pInstance;

	Singleton& operator=(const Singleton) = delete;
	Singleton(const Singleton&) = delete;
	//		//		//
};

template <typename T>
Singleton<T>::Singleton()
{
	s_pInstance = static_cast<T*>(this);
}

template <typename T>
Singleton<T>::~Singleton()
{
	s_pInstance = nullptr;
}

template <typename T>
T& Singleton<T>::Instance()
{
	if (!s_pInstance)
	{
		s_pInstance = new T();
	}

	return *s_pInstance;
}

template <typename T>
void Singleton<T>::Destroy()
{
	delete s_pInstance;
}
