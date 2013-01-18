#ifndef _INTROSTATE_
#define _INTROSTATE_

#include "gamestate.h"

/************************************************************************/
/* IntroState.h
The intro state provides a greating and instructions to the player.

Author: Jonathan Hanks (jonhanks@gmail.com)
*/
/************************************************************************/
class IntroState :
	public GameState
{
public:
	IntroState(ZombieGame* pOwnerGame);
	virtual ~IntroState(void);

	virtual void Init(int nCurrTime);
	//virtual void Update(int nCurrTime);
	virtual void Enter();
	//virtual void Exit();
	virtual void Draw();

	virtual void MousePress(int nButton, int nMouseState, int nXPos, int nYPos);
};

#endif