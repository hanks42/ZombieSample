#include ".\entity.h"
#include <math.h>

Entity::Entity(void)
{
	// initialize the entities data
	m_nXPos = 0;
	m_nYPos = 0;
	m_ThisEntityIs = E_TYPE_NONE;
	m_bIsAlive = 0;
	m_nKillVal = 0;
	m_nSaveVal = 0;
	m_nSpeed = 0;
	m_bNegMoveOnX = false;
	m_bNegMoveOnY = false;
	m_bPosMoveOnX = false;
	m_bPosMoveOnY = false;
	m_nLastUpdateTime = 0;
	m_nLastMoveTime = 0;
}	

Entity::~Entity(void)
{
}

void Entity::Update(int nCurrTime)
{
	// check to see it if is movement time
	bool bMoveTime = false;

	// if this is the first time then yes make movements
	if (m_nLastMoveTime == 0)
	{
		bMoveTime = true;
		
	}
	
	// otherwise if it has been long enough since the last move make a move
	if (m_nSpeed)
	{
		if ((nCurrTime - m_nLastMoveTime) > (1000/m_nSpeed))
		{
			bMoveTime = true;
		}
	}

	if (bMoveTime)
	{
		m_nLastMoveTime = nCurrTime;

		// check x and y movements and make any movements requested
		if (m_bNegMoveOnX)
		{
			m_nXPos--;
			m_bNegMoveOnX = false;
		}
		if (m_bNegMoveOnY)
		{
			m_nYPos--;
			m_bNegMoveOnY = false;
		}
		if (m_bPosMoveOnX)
		{
			m_nXPos++;
			m_bPosMoveOnX = false;
		}
		if (m_bPosMoveOnY)
		{
			m_nYPos++;
			m_bPosMoveOnY = false;
		}
	}

	// save this time as the last update time
	m_nLastUpdateTime = nCurrTime;
}

float Entity::GetDistanceTo(Entity* pEntity)
{
	// check the distance to the entity

	// get the absolute value of the differences in position
	// find the length of this and that will tell us if it's in range
	// good old a^2 + b^2 = c^2

	int nXAbs = abs(m_nXPos - pEntity->GetX());
	int nYAbs = abs(m_nYPos - pEntity->GetY());

	float fDist = sqrt(  ((float)(nXAbs*nXAbs)) + ((float)(nYAbs*nYAbs))  );

	return fDist;
}