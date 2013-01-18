#ifndef _WINSTATE_
#define _WINSTATE_

#include "gamestate.h"

/************************************************************************/
/* WinState.h
This is the win state where the player goes when they win. A win is when
they have killed all the zombies and their are persons remaining to
repopulate the city.

Author: Jonathan Hanks (jonhanks@gmail.com)
*/
/************************************************************************/
class WinState :
	public GameState
{
public:
	WinState(ZombieGame* pOwnerGame);
	virtual ~WinState(void);

	virtual void Init(int nCurrTime);
	virtual void Update(int nCurrTime);
	virtual void Enter();
	//virtual void Exit();
	virtual void Draw();

	virtual void MousePress(int nButton, int nMouseState, int nXPos, int nYPos);

protected:

	// helper functions

	// records the time that this state is entered so it is not left too soo
	void RecordEnterTime();			

	bool m_bGoToPlay;
	// go back to playstate

	int m_nEnterTime;
	// time that this state was entered so we don't leave to soon from a click
};

#endif