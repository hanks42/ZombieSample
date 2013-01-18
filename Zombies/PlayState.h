#ifndef _PLAYSTATE_
#define _PLAYSTATE_

#include "ZombieGame.h"
#include "GameState.h"
#include "Zombie.h"
#include "Person.h"
#include "Player.h"

#include <vector>


/************************************************************************/
/* PlayState.h
	The play state is where most of the game will occur, it handles all of
	the main part of the gameplay.
	
	Author: Jonathan Hanks (jonhanks@gmail.com)
	*/
/************************************************************************/
class PlayState : public GameState
{
public:
	PlayState(ZombieGame* pOwnerGame);
	virtual ~PlayState(void);

	virtual void Init(int nCurrTime);
	virtual void Update(int nCurrTime);
	virtual void Enter();
	//virtual void Exit();
	virtual void Draw();

	virtual void KeyPress(unsigned char key, int nXPos, int nYPos);
	virtual void MousePress(int nButton, int nMouseState, int nXPos, int nYPos);

protected:

	// helper functions
	// drawing functions
	void DrawAllZombies();
	void DrawAllPersons();
	void DrawPlayer();
	void DrawScore();
	// generation functions for game starts
	void GenerateRandomZombies();
	void GenerateRandomPersons();
	void GenerateRandomPlayer();

	void UpdateAllEntities(int nCurrTime);	// update all zombies and other entities
	void AttemptToFireBomb();				// fire the bomb if we can	
	bool IsInBombRange(Entity* pEntity);	// see if an entity is in range for the bomb
	void CheckEndConditions();			// check for game ending conditions
	void CalculateEndScore();			// calculate and update the ending score

	// list of zombies
	std::vector<Zombie*> m_vZombieList;

	// list of persons
	std::vector<Person*> m_vPersonList;

	// player character
	Player* m_pPlayer;
};

#endif