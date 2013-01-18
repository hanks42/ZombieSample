#ifndef _PERSON_
#define _PERSON_

#include "entity.h"

/************************************************************************/
/* Person.h
Persons are all of the little people in the world that zombies like to
feast on. Our heros job is to save them. Their specific functions and
routines go in here.

Author: Jonathan Hanks (jonhanks@gmail.com)
*/
/************************************************************************/

class Person :
	public Entity
{
public:
	Person(void);
	virtual ~Person(void);

	virtual void Draw(ZombieGFX* pGFXManager);

	// This resets the persons AI, should be used at the start of the round
	// when the person is randomly placed
	virtual void ResetAI();
};

#endif