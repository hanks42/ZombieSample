#include ".\zombie.h"
#include "ZombieGFX.h"
#include "defines.h"

#include <vector>

Zombie::Zombie(void)
{
	// turn this into a brain devouring zombie
	m_ThisEntityIs = E_TYPE_ZOMBIE;

	// initialize data
	m_pVictim = NULL;
	m_ZombieState = Z_AIS_NONE;

	m_nXDest = -1;
	m_nYDest = -1;

	m_bVictimSpotted = false;
	m_bLostVictim = true;
	
	m_nDevourStartTime = 0;
	
}

Zombie::~Zombie(void)
{
}

void Zombie::Draw(ZombieGFX* pGFXManager)
{
	if (pGFXManager)
		pGFXManager->DrawZombie(m_nXPos, m_nYPos);
}


void Zombie::ResetAI()
{
	// Reset each of the zombies ai related variables
	m_pVictim = NULL;
	m_ZombieState = Z_AIS_NONE;

	m_nXDest = -1;
	m_nYDest = -1;

	m_bVictimSpotted = false;
	m_bLostVictim = true;

	m_nDevourStartTime = 0;
}

void Zombie::Look(std::vector<Person*> vPersonList)
{
	// am I alive
	if (!m_bIsAlive)
		return;

	// if chasing look around to see where your current victim is
	//	and if out of range
	if (m_ZombieState == Z_AIS_CHASE)
	{
		// see if you lost the victim
		if (GetDistanceTo(m_pVictim) > ZOMBIE_VISION_RANGE)
		{
			m_bLostVictim = true;
		}
		// also check to see if the victim died
		if (!m_pVictim->IsAlive())
		{
			m_bLostVictim = true;
		}
	}
	// if wandering look for a new victim
	if (m_ZombieState == Z_AIS_WANDER)
	{
		// check each person in the person list
		for (int i = 0; i < vPersonList.size(); i++)
		{
			// make sure this victim is alived
			if (vPersonList[i]->IsAlive())
			{
				if (GetDistanceTo(vPersonList[i]) <= ZOMBIE_VISION_RANGE)
				{
					// found the new victim
					m_bVictimSpotted  = true;
					m_pVictim = vPersonList[i];
					break;
				}
			}
		}
	}
}

void Zombie::Update(int nCurrTime)
{
	// am I alive
	if (!m_bIsAlive)
	{
		Entity::Update(nCurrTime);
		return;
	}

	// find ai mode
	switch (m_ZombieState)
	{
		case Z_AIS_CHASE:
		{
			// chase mode

			// see if we lost the victim
			if (m_bLostVictim)
			{
				m_bLostVictim = false;
				m_pVictim = NULL;
				// change to wander mode
				m_ZombieState = Z_AIS_WANDER;
			}
			// see if we caught the victim
			if (CaughtVictim())
			{
				// start the feasting
				m_pVictim->SetAlive(false);
				m_ZombieState = Z_AIS_DEVOUR;
				m_nDevourStartTime = nCurrTime;
			}

			break;
		}
		case Z_AIS_WANDER:
		{
			// see if we spotted a victim
			if (m_bVictimSpotted)
			{
				m_bVictimSpotted = false;
				// set the destination to the victims position
				SetDestination(m_pVictim->GetX(), m_pVictim->GetY());
				// move to chase mode
				m_ZombieState = Z_AIS_CHASE;

			}
			// see if we reached our destination and need a new one
			if ((m_nXDest == -1) && (m_nYDest == -1))
			{
				// determine a new random destination
				SetRandomDestination(ZOMBIE_WANDER_RANGE);
			}

			break;
		}
		case Z_AIS_DEVOUR:
		{
			// devour the victim for the needed amount of time
			// basicly stand still
			if ((nCurrTime - m_nDevourStartTime) < DEVOUR_TIME)
			{
				// still devouring do nothing
			}
			else
			{
				// start to wandering again
				m_ZombieState = Z_AIS_WANDER;
			}

			break;
		}
		case Z_AIS_NONE:
		{
			// nothing to do here change to wander mode
			m_ZombieState = Z_AIS_WANDER;
			break;
		}
		default:
		{
			// no AI state this shouldn't happen
			// nothing to do here change to wander mode
			m_ZombieState = Z_AIS_WANDER;
			break;
		}
	}

	// check the zombie for movement
	CheckZombieMovement();

	Entity::Update(nCurrTime);
}

void Zombie::SetDestination(int nXDest, int nYDest)
{
	m_nXDest = nXDest;
	m_nYDest = nYDest;
}

void Zombie::SetRandomDestination(int nRange)
{
	// set the destition to bottom left cornor of the 
	// destination square range around the zombie
	int nNewDestX = m_nXPos - (nRange/2);
	int nNewDestY = m_nYPos - (nRange/2);

	// now increment this destination within the range to find the
	// resulting random destination in the range of the zombie
	nNewDestX += (int)( (rand()/(float)RAND_MAX) * nRange );
	nNewDestY += (int)( (rand()/(float)RAND_MAX) * nRange );

	// save the new destination
	m_nXDest = nNewDestX;
	m_nYDest = nNewDestY;

	// check to see if this destination is valid and if not do it again
	if ( (nNewDestX < 0) || (nNewDestY < 0) || (nNewDestX > GRID_SIZE_X) || (nNewDestY > GRID_SIZE_Y))
		SetRandomDestination(nRange);
}


void Zombie::CheckZombieMovement()
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

bool Zombie::CaughtVictim()
{
	// see if we are at the same position as our victim
	if (!m_pVictim)
		return false;

	return ((m_nXPos == m_pVictim->GetX()) && (m_nYPos == m_pVictim->GetY()));
}