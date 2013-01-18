#include ".\playstate.h"
#include "ZombieGame.h"
#include "Defines.h"

#include <math.h>
#include <glut.h>	


PlayState::PlayState(ZombieGame* pOwnerGame)
: GameState(pOwnerGame)
{
	m_pPlayer = NULL;

	// tell this state it is the play state
	m_ThisStateIs = Z_STATE_PLAY;
}

PlayState::~PlayState(void)
{
	// clean up the zombies and persons
	for (int i = 0; i < m_vZombieList.size(); i++)
	{
		delete m_vZombieList[i];
	}
	for (int j = 0; j < m_vPersonList.size(); j++)
	{
		delete m_vPersonList[j];
	}

	// clean up the player
	delete m_pPlayer;
}

void PlayState::Draw()
{
	ZombieGFX* pGFXManager = m_pOwnerGame->GetGFXManager();
	if (!pGFXManager)
		return;

	// clear the screen
	pGFXManager->ClearScreen();

	// draw the game board
	//pGFXManager->DrawFullGrid();

	// Draw the zombies
	DrawAllZombies();

	// Draw the people
	DrawAllPersons();

	// draw the player
	DrawPlayer();

	// Draw the Score
	DrawScore();

	// post the screen
	pGFXManager->PostScreen();

}

void PlayState::Init(int nCurrTime)
{
	// create the zombies and persons

	int nNumZombies = m_pOwnerGame->GetNumZombies();
	int nNumPersons = m_pOwnerGame->GetNumPersons();

	Zombie* pNewZombie = NULL;
	Person* pNewPerson = NULL;

	// create the zombies
	for (int i = 0; i < nNumZombies; i++)
	{
		pNewZombie = new Zombie();
		m_vZombieList.push_back(pNewZombie);
	}

	// create the persons
	for (int j = 0; j < nNumPersons; j++)
	{
		pNewPerson = new Person();
		m_vPersonList.push_back(pNewPerson);
	}

	// create the player
	m_pPlayer = new Player();

	GameState::Init(nCurrTime);
}

void PlayState::Enter()
{	
	// reset the players score
	m_pOwnerGame->ResetScore();

	// generate the entities in the game
	GenerateRandomZombies();
	GenerateRandomPersons();
	GenerateRandomPlayer();

	GameState::Enter();
}

void PlayState::Update(int nCurrTime)
{
	// check ending conditions
	CheckEndConditions();

	// call update for all of the entities
	UpdateAllEntities(nCurrTime);

	GameState::Update(nCurrTime);
}

void PlayState::KeyPress(unsigned char key, int nXPos, int nYPos)
{
	// allow for player movement with the "wasd" controls
	if(key == 'q') 
	{
		m_pOwnerGame->Quit();
	}
	if(key == 'l')
	{
		m_pOwnerGame->SetState(Z_STATE_LOSE);
	}
	if(key == 'w')
	{
		m_pOwnerGame->SetState(Z_STATE_WIN);
	}
	GameState::KeyPress(key, nXPos, nYPos);
}

void PlayState::MousePress(int nButton, int nMouseState, int nXPos, int nYPos)
{
	// on a left click make a destination for the player

	// Theres a bug in here, if the window is resized this won't work quite right
	// because the mouse position get all garbled but I think it's a problem with glut
	if (nButton == GLUT_LEFT_BUTTON)
	{
		// make sure the destination is valid
		if (
			(nXPos > 0) 
			/*&& (nXPos < m_pOwnerGame->GetBoardWidth()) */
			&& (nYPos > 0) 
			/*&& (nYPos < m_pOwnerGame->GetBoardHeight())*/
			)
		{
			m_pPlayer->SetDestination(nXPos, nYPos);
		}
	}

	// The bomb!!!
	if (nButton == GLUT_RIGHT_BUTTON)
	{
		// player set off the bomb
		AttemptToFireBomb();
	}

	GameState::MousePress(nButton, nMouseState, nXPos, nYPos);
}

void PlayState::DrawAllZombies()
{
	// call each zombies draw
	for (int i = 0; i < m_vZombieList.size(); i++)
	{
		// make sure they are alive
		if (m_vZombieList[i]->IsAlive())
			m_vZombieList[i]->Draw(m_pOwnerGame->GetGFXManager());
	}
}

void PlayState::DrawAllPersons()
{
	// call each persons draw
	for (int i = 0; i < m_vPersonList.size(); i++)
	{
		if (m_vPersonList[i]->IsAlive())
			m_vPersonList[i]->Draw(m_pOwnerGame->GetGFXManager());
	}
}

void PlayState::DrawPlayer()
{
	// call the draw routine for the player
	if (m_pPlayer->IsAlive())	// the player shouldn't be able to die
		m_pPlayer->Draw(m_pOwnerGame->GetGFXManager());
}

void PlayState::DrawScore()
{
	if (m_pOwnerGame->GetGFXManager())
		m_pOwnerGame->GetGFXManager()->DrawScore(m_pOwnerGame->GetScore());
}

void PlayState::GenerateRandomZombies()
{

	// generate random data for each of the persons and zombies
	int nRandX = 0;
	int nRandY = 0;
	int nRandSpeed = 0;

	// zombie generation loop
	for (int i = 0; i < m_vZombieList.size(); i++)
	{
		// make a random position
		nRandX = (int) (((float)rand()/RAND_MAX)*m_pOwnerGame->GetBoardWidth());
		nRandY = (int) (((float)rand()/RAND_MAX)*m_pOwnerGame->GetBoardHeight());

		// random speed between 1 and 4
		nRandSpeed	= rand() % ZOMBIE_SPEED;
		nRandSpeed++;

		// set the zombies data
		m_vZombieList[i]->SetX(nRandX);
		m_vZombieList[i]->SetY(nRandY);
		m_vZombieList[i]->SetAlive(true);
		m_vZombieList[i]->SetSpeed(nRandSpeed);
		m_vZombieList[i]->SetKillVal(ZOMBIE_KILL_SCORE);	// 1 point for zombie kills
		m_vZombieList[i]->SetSaveVal(ZOMBIE_SAVE_SCORE);	// -1 point for letting zombies live
		m_vZombieList[i]->ResetAI();

	}
}

void PlayState::GenerateRandomPersons()
{

	// generate random data for each of the persons and zombies
	int nRandX = 0;
	int nRandY = 0;
	int nRandSpeed = 0;

	// person generation loop
	for (int j = 0; j < m_vPersonList.size(); j++)
	{
		// make a random position
		nRandX = (int) (((float)rand()/RAND_MAX)*m_pOwnerGame->GetBoardWidth());
		nRandY = (int) (((float)rand()/RAND_MAX)*m_pOwnerGame->GetBoardHeight());

		// set the zombies data
		m_vPersonList[j]->SetX(nRandX);
		m_vPersonList[j]->SetY(nRandY);
		m_vPersonList[j]->SetAlive(true);
		m_vPersonList[j]->SetSpeed(PERSON_SPEED);		// people can't move for now
		m_vPersonList[j]->SetKillVal(PERSON_KILL_SCORE);	// lose a point for killing people
		m_vPersonList[j]->SetSaveVal(PERSON_KILL_SCORE);	// get 5 points for each person you save
		m_vPersonList[j]->ResetAI();

	}
}

void PlayState::GenerateRandomPlayer()
{

	// generate random data for the player
	int nRandX = 0;
	int nRandY = 0;

	// make a random position
	nRandX = (int) (((float)rand()/RAND_MAX)*m_pOwnerGame->GetBoardWidth());
	nRandY = (int) (((float)rand()/RAND_MAX)*m_pOwnerGame->GetBoardHeight());

	// set the zombies data
	m_pPlayer->SetX(nRandX);
	m_pPlayer->SetY(nRandY);
	m_pPlayer->SetAlive(true);
	m_pPlayer->SetSpeed(PLAYER_SPEED);		// people can't move for now
	m_pPlayer->SetKillVal(PLAYER_KILL_SCORE);	// this shouldn't happen
	m_pPlayer->SetSaveVal(PLAYER_SAVE_SCORE);	// get 50 points for surviving
}

void PlayState::UpdateAllEntities(int nCurrTime)
{
	// call update for the zombies
	for (int i = 0; i < m_vZombieList.size(); i++)
	{
		m_vZombieList[i]->Look(m_vPersonList);
		m_vZombieList[i]->Update(nCurrTime);
	}
	// call update for the persons
	for (int j = 0; j < m_vPersonList.size(); j++)
	{
		m_vPersonList[j]->Update(nCurrTime);
	}
	// call update for the player
	m_pPlayer->Update(nCurrTime);
}

void PlayState::AttemptToFireBomb()
{
	// check to see if we can fire
	if (!m_pPlayer->FireBomb())
		return;

	// here we fired the bomb so kill the appropriate zombies and persons
	// and adjust the score
	for (int i = 0; i < m_vZombieList.size(); i++)
	{
		// make sure they are alive
		if (m_vZombieList[i]->IsAlive())
		{
			// and in bomb range
			if (IsInBombRange(m_vZombieList[i]))
			{
				// kill this zombie and get the points
				m_vZombieList[i]->SetAlive(false);
				m_pOwnerGame->ChangeScore(m_vZombieList[i]->GetKillVal()	);
			}
		}
	}

	// now check persons
	for (int i = 0; i < m_vPersonList.size(); i++)
	{
		// make sure they are alive
		if (m_vPersonList[i]->IsAlive())
		{
			// and in bomb range
			if (IsInBombRange(m_vPersonList[i]))
			{
				// kill this zombie and get the points
				m_vPersonList[i]->SetAlive(false);
				m_pOwnerGame->ChangeScore(m_vPersonList[i]->GetKillVal()	);
			}
		}
	}
}

bool PlayState::IsInBombRange(Entity* pEntity)
{
	// get the absolute value of the differences in position
	// find the length of this and that will tell us if it's in range
	// good old a^2 + b^2 = c^2

	int nXAbs = abs(m_pPlayer->GetX() - pEntity->GetX());
	int nYAbs = abs(m_pPlayer->GetY() - pEntity->GetY());

	float fDist = sqrt(  ((float)(nXAbs*nXAbs)) + ((float)(nYAbs*nYAbs))  );

	if (fDist <= BOMB_RANGE)
		return true;
	else
		return false;
}

void PlayState::CheckEndConditions()
{
	// lose if all person are dead
	bool bLivingPerson = false;
	for (int i = 0; i < m_vPersonList.size(); i++)
	{
		if (m_vPersonList[i]->IsAlive())
		{
			// a living person
			bLivingPerson = true;
			break;
		}
	}

	if (!bLivingPerson)
	{
		// all persons dead you lose
		m_pOwnerGame->SetState(Z_STATE_LOSE);
		// update score
		CalculateEndScore();
		return;
	}

	// win if all zombies are dead
	bool bLivingZombie = false;
	for (int i = 0; i < m_vZombieList.size(); i++)
	{
		if (m_vZombieList[i]->IsAlive())
		{
			// a living person
			bLivingZombie = true;
			break;
		}
	}

	if (!bLivingZombie)
	{
		// all persons dead you lose
		m_pOwnerGame->SetState(Z_STATE_WIN);
		// update score
		CalculateEndScore();
		return;
	}

}

void PlayState::CalculateEndScore()
{

}