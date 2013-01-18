#ifndef _PLAYER_
#define _PLAYER_

#include "entity.h"

/************************************************************************/
/* Player.h
Player is the class of entity that represents the hero in the game. 
Things specific to the hero and it's actions will go in here.

Author: Jonathan Hanks (jonhanks@gmail.com)
*/
/************************************************************************/
class Player :
	public Entity
{
public:
	Player(void);
	virtual ~Player(void);

	virtual void Draw(ZombieGFX* pGFXManager);

	virtual void SetPosXMove() {m_bPosMoveOnX = true;}
	virtual void SetPosYMove() {m_bPosMoveOnY = true;}
	virtual void SetNegXMove() {m_bNegMoveOnX = true;}
	virtual void SetNegYMove() {m_bNegMoveOnY = true;}

	virtual void SetDestination(int nXDest, int nYDest);

	virtual void Update(int nCurrTime);

	// notification that the player wishes to fire the bomb
	virtual bool FireBomb();

protected:
	
	// helper functions
	void CheckPlayerMovement();
	void CheckForBombFiring(int nCurrTime);
	void CheckForBombAnimation(int nCurrTime);
	void UpdateBombRotation(int nCurrTime);

	int m_nXDest;
	// x destination of the player
	int m_nYDest;
	// y destination of the player

	int m_nLastBombTime;
	// last time the bomb was fired, it can only be fired once every few secs

	bool m_bCanFireBomb;
	// whether or not the player can fire the bomb

	bool m_bDoBombFire;
	// do the bomb firing animation

	bool m_bShowBombAnim;
	// show the bomb animation this frame

	float m_fBombRotation;
	// used to rotate the bomb animation around
};

#endif