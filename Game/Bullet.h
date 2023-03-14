#pragma once
#include "GameObject.h"

enum class GAMESTATE_ENUM;

class Bullet : public GameObject
{
public:
	Bullet(Play::Point2f pos);

	~Bullet();


	void Update() override;
	void UpdateDestroyed();
	void Draw() override;



	friend class Tank;
private:
	GridPos m_gridPos;
};


