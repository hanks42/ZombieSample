#ifndef _ZOMBIE_
#define _ZOMBIE_

#include "entity.h"
#include "Person.h"

#include <vector>

/************************************************************************/
/* Zombie.h
Zombies are the villains, they want to eat all the brains in the world and
we must stop them. Any specific routines of the zombie go in here including
their AI routines.

Author: Jonathan Hanks (jonhanks@gmail.com)
*/
/************************************************************************/
enum ZombieAIState
{
	// all the available ai states for the zombies
	Z_AIS_MIN = 0,
	Z_AIS_WANDER,	// wander around randomly to find a victim
	Z_AIS_CHASE,	// chase a target victim until you catch it or it leaves range
	Z_AIS_DEVOUR,	// devour a victim once caught
	Z_AIS_NONE,
	Z_AIS_MAX
};

class Zombie :
	public Entity
{
public:
	Zombie(void);
	virtual ~Zombie(void);

	virtual void Draw(ZombieGFX* pGFXManager);

	// This allows the zombie to look around and see where his victim is or if he 
	//	sees a new victim or if the current victim is out of range
	//	This should be called each update
	virtual void Look(std::vector<Person*> vPersonList);

	// The zombies think routine
	virtual void Update(int nCurrTime);

	// this resets the zombies AI, used for when the zombie is initially placed
	virtual void ResetAI();

protected:

	// helper functions
	void CheckZombieMovement();		// check to see where the zombie needs to move
	bool CaughtVictim();			// see if the zombie has caught his victim
	void SetDestination(int nXDest, int nYDest);		// update the zombies destination
	void SetRandomDestination(int nRange);				// sets a random destination for the zombie
														// inside of the range given


	// data
	Person* m_pVictim;
	// the selected victim of the zombie, will chase any selected victim once
	// they are selected until they are caught and their brains are devoured
	// or until they leave the zombies vision range

	ZombieAIState m_ZombieState;
	// the AI state that the zombie is currently in

	int m_nXDest;
	int m_nYDest;
	// The zombies destination, used for wander mode

	bool m_bVictimSpotted;
	// This is used to break the zombie out of wandering mode when he
	// finds a victim

	bool m_bLostVictim;
	// if the zombie lost the victim they ran too fast for the slow
	// brain eater

	int m_nDevourStartTime;
	// this is used to impose the delay that the zombie must
	// use to devour his victims brains, during this time he stands still
	// and eats the victim

};

#endif