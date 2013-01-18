#ifndef _LOSESTATE_
#define _LOSESTATE_

#include "gamestate.h"

/************************************************************************/
/* LoseState.h
This is the loss state that occurs when the player loses the game. A loss
happens when there are no civilians left and their are zombies remaining.

Author: Jonathan Hanks (jonhanks@gmail.com)
*/
/************************************************************************/
class LoseState :
	public GameState
{
public:
	LoseState(ZombieGame* pOwnerGame);
	virtual ~LoseState(void);

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