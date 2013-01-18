#include ".\introstate.h"
#include "GameState.h"

#include "ZombieGFX.h"

IntroState::IntroState(ZombieGame* pOwnerGame)
: GameState(pOwnerGame)
{
	// tell this state it is the play state
	m_ThisStateIs = Z_STATE_INTRO;
}

IntroState::~IntroState(void)
{
}

void IntroState::Draw()
{
	ZombieGFX* pGFXManager = m_pOwnerGame->GetGFXManager();
	if (!pGFXManager)
		return;

	// clear the screen
	pGFXManager->ClearScreen();

	// draw the intro screen that waits for a click to begin
	pGFXManager->DrawIntro();

	// post the screen
	pGFXManager->PostScreen();
}

void IntroState::Init(int nCurrTime)
{
	GameState::Init(nCurrTime);
}

void IntroState::Enter()
{
	
	GameState::Enter();
}

void IntroState::MousePress(int nButton, int nMouseState, int nXPos, int nYPos)
{
	// change to play state on a key press
	m_pOwnerGame->SetState(Z_STATE_PLAY);

	GameState::MousePress(nButton, nMouseState, nXPos, nYPos);
}