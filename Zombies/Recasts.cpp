#include "Recasts.h"
#include "main.h"
#include "ZombieGame.h"

/************************************************************************/
/* This is used to recast the display function to the one in the
	game class.
	*/
/************************************************************************/
void recastDisplay()
{
	g_pZombieGame->Run();
}
void recastMousePress(int nButton, int nState, int nXPos, int nYPos)
{
	g_pZombieGame->MousePress(nButton, nState, nXPos, nYPos);
}
void recastMouseMove(int nXPos, int nYPos)
{
	g_pZombieGame->MouseMove(nXPos, nYPos);
}
void recastKeyPress(unsigned char cKey, int nXPos, int nYPos)
{
	g_pZombieGame->KeyPress(cKey, nXPos, nYPos);
}