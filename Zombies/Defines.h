#ifndef _DEFINES_
#define _DEFINES_

// the size of the game grid in game world coordinates
const int GRID_SIZE_X = 400;
const int GRID_SIZE_Y = 400;

// some data for the entities
const int PLAYER_SPEED = 20;
const int ZOMBIE_SPEED = 4;
const int PERSON_SPEED = 0;
const int PLAYER_KILL_SCORE = -100;
const int ZOMBIE_KILL_SCORE = 2;
const int PERSON_KILL_SCORE = -4;
const int PLAYER_SAVE_SCORE = 50;
const int ZOMBIE_SAVE_SCORE = -10;
const int PERSON_SAVE_SCORE = 10;

// bombs
const int BOMB_RANGE = 25;
const int BOMB_RECHARGE = 2500;
const int BOMB_ANIM_TIME = 750;
const float BOMB_ROT_FACTOR = 55.0f;

// population
const int NUM_ZOMBIES = 1;
const int NUM_PERSONS = 40;

// Zombie AI values
const int DEVOUR_TIME = 2000;
const int ZOMBIE_VISION_RANGE = 30;
const int ZOMBIE_WANDER_RANGE = 60;		// higher the number the less random the wandering should appear
										//	(the zombie picks a destination in this range and goes to it
										//	when it has nothing else to do) this is a square around the zombie

// state stuff
const int STATE_SCREEN_DELAY = 3000;	// we want to stay at the state screens for at least 3 seconds

#endif