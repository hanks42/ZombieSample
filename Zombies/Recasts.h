#ifndef _DISPLAY_
#define _DISPLAY_

// Used to recast the zombie game functions so they can be used
// with glut
void recastDisplay();
void recastMousePress(int nButton, int nState, int nXPos, int nYPos);
void recastMouseMove(int nXPos, int nYPos);
void recastKeyPress(unsigned char cKey, int nXPos, int nYPos);

#endif