#include "Play.h"
#include "Common.h"
#include "ParticlesCommon.h"

#include "GameManager.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "GameArea.h"
#include "Bullet.h"

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
		Fire();
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
	DrawSprite(m_crosshairSprite, m_mousePos, 0);
}

void Tank::Fire()
{
	using namespace Play;

	Vector2f normBulletVel = NormaliseVector(m_mousePos - m_worldPos);

	normBulletVel *= m_bulletVelocity;

	Bullet* newBullet = static_cast<Bullet*>(GameObjectManager::Instance().Create(GameObjectType::TYPE_BULLET, m_worldPos));

	newBullet->m_velocity = normBulletVel * m_bulletVelocity;
	newBullet->m_matrix = newBullet->m_matrix * MatrixRotation(AngleBetweenTwoVectors({ 0.f, 1.f }, normBulletVel));
	newBullet->m_matrix.row[2] = m_worldPos;
}
