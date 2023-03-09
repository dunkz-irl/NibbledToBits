#pragma once

#include "Singleton.h"

enum class GameObjectType;
class GameObject;

class GameObjectManager final : public Singleton<GameObjectManager>
{
public:
	GameObject* Create(GameObjectType type, Play::Point2f pos);
	void UpdateAll();
	void DrawAll();
	void CleanupAll();

	void CleanupAllOfType(GameObjectType type);
	void Register(GameObject* obj) { m_v_pGameObjects.push_back(obj); };

	std::vector<GameObject*> GetGameObjectsOfType(GameObjectType type);

private:
	std::vector<GameObject*> m_v_pGameObjects;
};
