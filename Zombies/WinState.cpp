#include ".\WinState.h"
#include "GameState.h"
#include "Defines.h"

#include "ZombieGFX.h"

WinState::WinState(ZombieGame* pOwnerGame)
: GameState(pOwnerGame)
{
	// tell this state it is the play state
	m_ThisStateIs = Z_STATE_WIN;

	m_bGoToPlay = false;
}

WinState::~WinState(void)
{
}

void WinState::Draw()
{
	ZombieGFX* pGFXManager = m_pOwnerGame->GetGFXManager();
	if (!pGFXManager)
		return;

	// clear the screen
	pGFXManager->ClearScreen();

	// draw the intro screen that waits for a click to begin
	pGFXManager->DrawWinMessage();

	// draw the final score
	pGFXManager->DrawFinalScore(m_pOwnerGame->GetScore());

	// post the screen
	pGFXManager->PostScreen();
}

void WinState::Init(int nCurrTime)
{
	GameState::Init(nCurrTime);
}

void WinState::Update(int nCurrTime)
{
	// make sure we stay in this state for the minimum delay time
	if (m_bGoToPlay)
	{
		if ((nCurrTime  - m_nEnterTime) > STATE_SCREEN_DELAY)
		{
			m_pOwnerGame->SetState(Z_STATE_PLAY);
		}
		else
		{
			m_bGoToPlay = false;
		}
	}

	GameState::Update(nCurrTime);
}

void WinState::Enter()
{
	RecordEnterTime();
	GameState::Enter();
}

void WinState::MousePress(int nButton, int nMouseState, int nXPos, int nYPos)
{
	// change to play state on a key press
	m_bGoToPlay = true;

	GameState::MousePress(nButton, nMouseState, nXPos, nYPos);
}

void WinState::RecordEnterTime()
{
	m_nEnterTime = m_nLastTime;
}