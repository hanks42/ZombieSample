#include ".\losestate.h"
#include "GameState.h"

#include "Defines.h"
#include "ZombieGFX.h"

LoseState::LoseState(ZombieGame* pOwnerGame)
: GameState(pOwnerGame)
{
	// tell this state it is the play state
	m_ThisStateIs = Z_STATE_LOSE;

	m_bGoToPlay = false;
}

LoseState::~LoseState(void)
{
}

void LoseState::Draw()
{
	ZombieGFX* pGFXManager = m_pOwnerGame->GetGFXManager();
	if (!pGFXManager)
		return;

	// clear the screen
	pGFXManager->ClearScreen();

	// draw the intro screen that waits for a click to begin
	pGFXManager->DrawLossMessage();

	// draw the final score
	pGFXManager->DrawFinalScore(m_pOwnerGame->GetScore());

	// post the screen
	pGFXManager->PostScreen();
}

void LoseState::Init(int nCurrTime)
{
	GameState::Init(nCurrTime);
}

void LoseState::Enter()
{
	// record the entry time so we can prevent an early exit
	RecordEnterTime();
	GameState::Enter();
}

void LoseState::Update(int nCurrTime)
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

void LoseState::MousePress(int nButton, int nMouseState, int nXPos, int nYPos)
{
	// change to play state on a key press
	m_bGoToPlay = true;

	GameState::MousePress(nButton, nMouseState, nXPos, nYPos);
}

void LoseState::RecordEnterTime()
{
	m_nEnterTime = m_nLastTime;
}