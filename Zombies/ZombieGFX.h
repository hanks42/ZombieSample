#ifndef _ZOMBIEGFX_
#define _ZOMBIEGFX_

/************************************************************************/
/* ZombieGFX
	This class handles all of the openGL graphics that the game needs to
	perform. The engines pretty simple and pretty much only does pixels
	and lines for now.

	Author: Jonathan Hanks (jonhanks@gmail.com)
	*/
/************************************************************************/
class ZombieGFX
{
public:
	ZombieGFX(void);
	virtual ~ZombieGFX(void);

	// Initialize the graphics system
	bool Init(int nWidth, int nHeight);

	// clear the screen to black, do this first or the last frame will show up as well as
	// the current one
	void ClearScreen();

	// switches the back buffers and displays what you drew
	void PostScreen();

	// Draws a full white grid onto the screen to represent the game board
	void DrawFullGrid();

	// place a zombie on the board
	void DrawZombie(int nXPos, int nYPos);

	// place a random person on the board
	void DrawPerson(int nXPos, int nYPos);

	// draws the player character
	void DrawPlayer(int nXPos, int nYPos);	

	// draws the score it is given
	void DrawScore(int nScore);

	// draws the bomb animation
	void DrawBomb(int nXPos, int nYPos, float fRotation);

	// draws the intro screen
	void DrawIntro();

	// draw the loss message
	void DrawLossMessage();

	// draw the winning message
	void DrawWinMessage();

	//draws the final score
	void DrawFinalScore(int nScore);

private:
	int m_nWinWidth;
	// the width of the window

	int m_nWinHeight;
	// the height of the window
};

#endif