#include ".\zombiegame.h"

#include "Recasts.h"
#include "PlayState.h"
#include "IntroState.h"
#include "LoseState.h"
#include "WinState.h"
#include "Defines.h"

#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <glut.h>		

ZombieGame::ZombieGame(void)
{
	// set window defaults
	m_nWinHeight = 400;
	m_nWinWidth = 400;
	m_bInitialized = false;

	// initialize data
	m_pCurrentState = NULL;
	m_pGFX = NULL;
	m_nNumPersons = NUM_PERSONS;		// one day I'll have an options screen and these will go there
	m_nNumZombies = NUM_ZOMBIES;			// that day is not today
	m_nScore = 0;
}

ZombieGame::~ZombieGame(void)
{
}

bool ZombieGame::Init(int nWidth, int nHeight)
{

	m_nWinWidth = nWidth;
	m_nWinHeight = nHeight;

	// create the graphics system and initialize it
	m_pGFX = new ZombieGFX();
	if (!m_pGFX)
		return false;

	// initialize the graphics system
	if (!m_pGFX->Init(m_nWinHeight, m_nWinHeight))
		return false;
		
	/* Create the call back functions for glut */
	glutDisplayFunc(recastDisplay);
	glutMouseFunc(recastMousePress);
	glutPassiveMotionFunc(recastMouseMove);
	glutKeyboardFunc(recastKeyPress);

	// seed the random number generator
	srand( (unsigned)time( NULL ) );

	// create and initialize all the states

	// create intro state
	IntroState* pNewIntroState = new IntroState(this);
	// make sure we got the memory for it
	if (!pNewIntroState)
		return false;
	pNewIntroState->Init(glutGet(GLUT_ELAPSED_TIME));
	m_vGameStates.push_back(pNewIntroState);

	// create playing state
	PlayState* pNewPlayState = new PlayState(this);
	// make sure we got the memory for it
	if (!pNewPlayState)
		return false;
	pNewPlayState->Init(glutGet(GLUT_ELAPSED_TIME));
	m_vGameStates.push_back(pNewPlayState);

	// create win state
	WinState* pNewWinState = new WinState(this);
	// make sure we got the memory for it
	if (!pNewWinState)
		return false;
	pNewWinState->Init(glutGet(GLUT_ELAPSED_TIME));
	m_vGameStates.push_back(pNewWinState);

	// create lose state
	LoseState* pNewLoseState = new LoseState(this);
	// make sure we got the memory for it
	if (!pNewLoseState)
		return false;
	pNewLoseState->Init(glutGet(GLUT_ELAPSED_TIME));
	m_vGameStates.push_back(pNewLoseState);
    
	m_bInitialized = true;

	return true;
}

bool ZombieGame::Cleanup()
{
	// delete the states in the state vector
	for (int i = 0; i < m_vGameStates.size(); i++)
	{
		delete m_vGameStates[i];
	}

	return true;
}

void ZombieGame::Go()
{
	// set the first state to be the intro state
	SetState(Z_STATE_INTRO);

	/* enter the main loop */
	glutMainLoop();
}

void ZombieGame::Run()
{

	// update the current state
	m_pCurrentState->Update(glutGet(GLUT_ELAPSED_TIME));

	// draw the current state
	m_pCurrentState->Draw();
}

void ZombieGame::SetState(ZombieGameState newState)
{
	// call exit on the current state
	if (m_pCurrentState)
		m_pCurrentState->Exit();

	// change the current state pointer to the new state
	for (int i = 0; i < m_vGameStates.size(); i++)
	{
		if (m_vGameStates[i]->GetStateType() == newState)
		{
			m_pCurrentState = m_vGameStates[i];
			break;
		}
	}

	// call enter on the new state
	if (m_pCurrentState)
		m_pCurrentState->Enter();
}

void ZombieGame::MousePress(int nButton, int nState, int nXPos, int nYPos)
{
	// mouse coords are inverted on Y
	nYPos = m_nWinHeight - nYPos;
	m_pCurrentState->MousePress(nButton, nState, nXPos, nYPos);
}

void ZombieGame::MouseMove(int nXPos, int nYPos)
{
	// mouse coords are inverted on Y
	nYPos = m_nWinHeight - nYPos;
	m_pCurrentState->MouseMove(nXPos, nYPos);
}

void ZombieGame::KeyPress(unsigned char cKey, int nXPos, int nYPos)
{
	// mouse coords are inverted on Y
	nYPos = m_nWinHeight - nYPos;
	m_pCurrentState->KeyPress(cKey, nXPos, nYPos);
}

void ZombieGame::Quit()
{
	// cleanup any used resources
	Cleanup();
	// exit the program
	exit(0);
}