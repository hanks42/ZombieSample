#ifndef _GAMESTATE_
#define _GAMESTATE_

#include "ZombieGame.h"

/************************************************************************/
/* Gamestate.h
	GameState is a base class that defines the behaviors that any state of
	the game should be able to perform. It is what all other states are built
	onto and allows for the state machine flow of the game to work.
	*/
/************************************************************************/

class ZombieGame;

enum ZombieGameState
{
	Z_STATE_MIN = 0,
	Z_STATE_INTRO,
	Z_STATE_PLAY,
	Z_STATE_WIN,
	Z_STATE_LOSE,
	Z_STATE_NONE,
	Z_STATE_MAX
};

class GameState
{
public:
	GameState(ZombieGame* pOwnerGame);
	virtual ~GameState(void);

	virtual ZombieGameState GetStateType();
	// Tells what this state is

	virtual void KeyPress(unsigned char key, int nXPos, int nYPos);
	// functionality for when a key is pressed in this state
	//	Params:
	//		key - the key pressed
	//		nXPos and nYPos - position of the mouse

	virtual void MouseMove(int nXPos, int nYPos);
	// functionality for when the mouse moves in this state
	//	Params:
	//		nXPos and nYPos - position of the mouse

	virtual void MousePress(int nButton, int nMouseState, int nXPos, int nYPos);
	// functionality for a press of one of the mouse buttons
	//	Params:
	//		nXPos and nYPos - position of the mouse
	//		nButton - which mouse button
	//		nMouseState - button going down or being released

	virtual void Init(int nCurrTime);
	// functionality to initialize all of this states variables

	virtual void Update(int nCurrTime);
	// function that updates any routines that need to be performed such as
	// AI routines or others

	virtual void Draw() = 0;
	// functionality to perform all of the draw routines that need to occur
	// based on what is happening

	virtual void Enter();
	// functionality that needs to occur when entering this state

	virtual void Exit();
	// functionality that occurs when exiting this state

protected:
	ZombieGameState m_ThisStateIs;
	// Whatever state this state actually is

	ZombieGame* m_pOwnerGame;
	// The game this state belongs to so it may talk to its parent

	int m_nLastTime;
	// The last time this state was updated
};

#endif