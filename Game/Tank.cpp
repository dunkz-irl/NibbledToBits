#include "Play.h"
#include "Common.h"
#include "ParticlesCommon.h"

#include "ParticleManager.h"
#include "GameManager.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "GameArea.h"
#include "Bullet.h"

#include <queue>

#include "Tank.h"

void Tank::Update()
{
	m_worldPos = GameArea::GameToWorld({ posx, posy });
	m_mousePos = GetMousePos();
	m_tankToCursorVec = m_mousePos - GameArea::GameToWorld({ posx, posy });

	if (GM_INST.m_currentGameState == GAMESTATE_ENUM::PLANNING)
		return;

	if (Play::KeyPressed(VK_LBUTTON))
	{
		// Don't fire if clicking on panel
		if (GameArea::WorldToGame(m_mousePos).x < 0 || GameArea::WorldToGame(m_mousePos).y < 0)
		{
			return;
		}

		// Don't fire if picking up object
		GameAreaObject* pObj_GA = GameArea::GetGameAreaObject(GameArea::WorldToGame(m_mousePos));
		
		if (GM_INST.m_currentHeld->id != -1)
		{
			return;
		}

		int bulletSpriteID = UseAmmo();

		if (bulletSpriteID == -1)
		{
			ParticleManager::Instance().CreateEmitter(EmitterType::SMOKEPUFFSMALL, m_matrix.row[2], 0.1f);
			return;
		}

		Fire(bulletSpriteID);
	}
}

void Tank::Draw()
{
	using namespace Play;

	// Turret
	Matrix2D turretMatrix = MatrixIdentity();

	turretMatrix = turretMatrix * MatrixRotation(AngleBetweenTwoVectors({ 0.f, 1.f }, m_tankToCursorVec));
	turretMatrix.row[2] = GameArea::GameToWorld({ posx, posy });

	DrawSpriteTransformed(Play::GetSpriteId(m_turretSprite), turretMatrix, 0);

	if (GM_INST.m_currentGameState == GAMESTATE_ENUM::PLANNING)	
		return;	

	// Crosshair
	// Don't draw if mouse is over panel
	if (GameArea::WorldToGame(m_mousePos).x < 0 || GameArea::WorldToGame(m_mousePos).y < 0)
		return;

	DrawSprite(m_crosshairSprite, m_mousePos, 0);
}

void Tank::AddAmmo(int id)
{
	m_ammunition.push(id);
}

int Tank::UseAmmo()
{
	if (m_ammunition.size() == 0)
		return -1;

	int type = m_ammunition.front();
	m_ammunition.pop();
	return type;
}

void Tank::Reset()
{
	m_ammunition = std::queue<int>();
}

void Tank::Fire(int bulletSpriteID)
{
	using namespace Play;

	Vector2f normBulletVel = NormaliseVector(m_mousePos - m_worldPos);
	Vector2f bulletVel = normBulletVel * m_bulletVelocity;

	Bullet* newBullet = static_cast<Bullet*>(GameObjectManager::Instance().Create(GameObjectType::TYPE_BULLET, m_worldPos));

	newBullet->m_velocity = normBulletVel * m_bulletVelocity;
	newBullet->m_matrix = newBullet->m_matrix * MatrixRotation(AngleBetweenTwoVectors({ 0.f, 1.f }, normBulletVel));
	newBullet->m_matrix.row[2] = m_worldPos + normBulletVel * static_cast<float>(SQUARE_SIZE);
	newBullet->m_spriteID = bulletSpriteID;
}