#include ".\player.h"
#include "ZombieGFX.h"
#include "Defines.h"
Player::Player(void)
{
	// our brave hero
	m_ThisEntityIs = E_TYPE_PLAYER;

	m_nXDest = -1;
	m_nYDest = -1;

	m_bCanFireBomb = false;
	m_nLastBombTime = 0;
	m_bShowBombAnim = false;
	m_bDoBombFire = false;
	m_fBombRotation = 0;
}

Player::~Player(void)
{
}

void Player::Draw(ZombieGFX* pGFXManager)
{
	if (pGFXManager)
	{
		pGFXManager->DrawPlayer(m_nXPos, m_nYPos);

		// show the bomb animation if needed
		if (m_bShowBombAnim)
		{
			pGFXManager->DrawBomb(m_nXPos, m_nYPos, m_fBombRotation);
		}
	}
}

void Player::SetDestination(int nXDest, int nYDest)
{
	m_nXDest = nXDest;
	m_nYDest = nYDest;
}

void Player::Update(int nCurrTime)
{
	CheckPlayerMovement();
	CheckForBombFiring(nCurrTime);
	CheckForBombAnimation(nCurrTime);
	UpdateBombRotation(nCurrTime);

	Entity::Update(nCurrTime);
}

void Player::CheckPlayerMovement()
{
	// check for a destination
	if ((m_nXPos == m_nXDest) && (m_nYPos == m_nYDest))	// arrived
	{
		// at the destination so clear it
		m_nXDest = -1;
		m_nYDest = -1;
	}

	// clear the movement since we will update it
	m_bPosMoveOnX = false;
	m_bNegMoveOnX = false;
	m_bPosMoveOnY = false;
	m_bNegMoveOnY = false;

	// move toward the destination if there is one
	if ((m_nXPos != m_nXDest) && (m_nXDest != -1))
	{
		if (m_nXPos > m_nXDest)
			m_bNegMoveOnX = true;
		else
			m_bPosMoveOnX = true;
	}
	if ((m_nYPos != m_nYDest) && (m_nYDest != -1))
	{
		if (m_nYPos > m_nYDest)
			m_bNegMoveOnY = true;
		else
			m_bPosMoveOnY = true;
	}
}

bool Player::FireBomb()
{
	// see if we can fire it now
	if (m_bCanFireBomb)
	{
		// make sure to do the animation
		m_bDoBombFire = true;
		return true;	
	}

	return false;
}

void Player::CheckForBombFiring(int nCurrTime)
{
	// did we just fire the bomb?
	if (m_bDoBombFire)
	{
		m_nLastBombTime = nCurrTime;
		m_bDoBombFire = false;
	}
	else
	{
		if ((nCurrTime - m_nLastBombTime) < BOMB_RECHARGE)
		{
			// can't fire the bomb yet
			m_bCanFireBomb = false;
		}
		else
		{
			m_bCanFireBomb = true;
		}
	}
}

void Player::CheckForBombAnimation(int nCurrTime)
{
	// if it has been less than half a second show the bomb animation
	if ((nCurrTime - m_nLastBombTime) < BOMB_ANIM_TIME )
	{
		m_bShowBombAnim = true;
	}
	else
	{
		m_bShowBombAnim = false;
	}
}

void Player::UpdateBombRotation(int nCurrTime)
{
	float fElapsedSec = (m_nLastUpdateTime - nCurrTime)/1000.0f;
	m_fBombRotation += fElapsedSec*BOMB_ROT_FACTOR;
}