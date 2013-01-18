#include ".\gamestate.h"

GameState::GameState(ZombieGame* pOwnerGame)
{
	m_pOwnerGame = pOwnerGame;
}

GameState::~GameState(void)
{
}

ZombieGameState GameState::GetStateType()
{
	return m_ThisStateIs;
}


void GameState::KeyPress(unsigned char key, int nXPos, int nYPos)
{

}

void GameState::MouseMove(int nXPos, int nYPos)
{

}

void GameState::MousePress(int nButton, int nMouseState, int nXPos, int nYPos)
{

}

void GameState::Init(int nCurrTime)
{
	m_nLastTime = nCurrTime;
}

void GameState::Update(int nCurrTime)
{
	m_nLastTime = nCurrTime;
}


void GameState::Enter()
{

}

void GameState::Exit()
{

}
