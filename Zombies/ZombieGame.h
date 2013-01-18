#ifndef _ZOMBIEGAME_
#define _ZOMBIEGAME_

#include <vector>

#include "GameState.h"
#include "ZombieGFX.h"

class GameState;
enum ZombieGameState;

/************************************************************************/
/* ZombieGame.h
	This class is the main shell of the game, it handles setting up all of the
	graphics and controlling the logic flow of the game.

	Author: Jonathan Hanks (jonhanks@gmail.com)
	*/
/************************************************************************/

class ZombieGame
{
public:
	// The constructor takes care of setting up the variable defaults
	//	but Init() must still be called before anything can happen
	ZombieGame(void);
	virtual ~ZombieGame(void);

	// The initialization function for the game, initializes glut and
	//	sets up all the needed variables and game screen. 
	//
	// Return: false if failed
	bool Init(int nWidth, int nHeight);

	// A cleanup function to clean up any memory the game used
	bool Cleanup();

	// The Go function starts the execution of the game, pretty much passes
	//	control of the program over to the ZombieGame class
	void Go();

	// The run function for use by glut, this function is called each frame and
	//	performs the tasks needed for the operation of the game
	void Run();

	// The quit function that allows the game to end
	void Quit();

	// Sets the current state of the game
	void SetState(ZombieGameState newState);

	// allows access to the players score
	int GetScore() {return m_nScore;}
	// changes the players score by the amount requested
	void ChangeScore(int nAmount) {m_nScore += nAmount;}
	// resets the players score
	void ResetScore() {m_nScore = 0;}

	ZombieGFX* GetGFXManager() {return m_pGFX;}

	// Data accessors for the game states and what not
	int GetNumZombies() {return m_nNumZombies;}
	int GetNumPersons() {return m_nNumPersons;}

	int GetBoardWidth() { return m_nWinWidth;}
	int GetBoardHeight() {return m_nWinHeight;}

	// Event management functions
	
	// Callback for Mouse button presses
	void MousePress(int nButton, int nState, int nXPos, int nYPos);
	// Callback for mouse moves
	void MouseMove(int nXPos, int nYPos);
	// callback for key press
	void KeyPress(unsigned char cKey, int nXPos, int nYPos);

private:
	int m_nWinWidth;
	// The default width of the window is 400

	int m_nWinHeight;
	// The default height of the window is 400

	bool m_bInitialized;
	// Whether the game has been initialized, nothing can be done until it is

	GameState* m_pCurrentState;
	// A pointer to the current game state

	std::vector<GameState*> m_vGameStates;
	// A list of all the game states currently created

	ZombieGFX* m_pGFX;
	// the zombie graphics system...brains!

	// game data
	int m_nNumZombies;
	// number of zombies that will infest the world
	int m_nNumPersons;
	// number of persons that are available for zombie lunches

	int m_nScore;
	// the players score


};

#endif