#ifndef _ENTITY_
#define _ENTITY_

#include "ZombieGFX.h"
/************************************************************************/
/* Entity.h
	Entity is the base entity that all things in the game will be based
	on. All people, zombies and the player are entities as well as anything
	that is created later would be an entity. Entities have a position,
	an entity type (set by the constructor of the child class) etc
	
	Author: Jonathan Hanks (jonhanks@gmail.com)
	*/
/************************************************************************/

enum EntityType
{
	E_TYPE_MIN = 0,
	E_TYPE_ZOMBIE,
	E_TYPE_PLAYER,
	E_TYPE_PERSON,
	E_TYPE_NONE,
	E_TYPE_MAX
};

class Entity
{
public:
	Entity(void);
	virtual ~Entity(void);

	// Each entity will draw itself when told
	virtual void Draw(ZombieGFX* pGFXManager) = 0;

	// each entity gets an update call each cycle to perform any 
	// thinking it would like to do
	virtual void Update(int nCurrTime);

	// accessors for the entities data
	virtual int GetX() {return m_nXPos;}
	virtual int GetY() {return m_nYPos;}
	virtual bool IsAlive() {return m_bIsAlive;}
	virtual EntityType GetEntityType() {return m_ThisEntityIs;}
	virtual int GetKillVal() {return m_nKillVal;}
	virtual int GetSaveVal() {return m_nSaveVal;}
	virtual int GetSpeed() {return m_nSpeed;}

	// mutators for the entities data
	virtual void SetX(int nXPos) {m_nXPos = nXPos;}
	virtual void SetY(int nYPos) {m_nYPos = nYPos;}
	virtual void SetAlive(bool bAlive) {m_bIsAlive = bAlive;}
	virtual void SetKillVal(int nKillVal) {m_nKillVal = nKillVal;}
	virtual void SetSaveVal(int nSaveVal) {m_nSaveVal = nSaveVal;}
	virtual void SetSpeed(int nSpeed) {m_nSpeed = nSpeed;}

	// find the distance from this entity to the other
	float GetDistanceTo(Entity* pEntity);

protected:
	int m_nXPos;
	// X position of the entity
	int m_nYPos;
	// Y position of the entity

	EntityType	m_ThisEntityIs;
	// the type of entity this is

	bool m_bIsAlive;
	// whether this entity is alive or dead

	int m_nKillVal;
	// the score value for killing this entity
	int m_nSaveVal;
	// the score value for saving this entity (being alive at end of the game)

	int m_nSpeed;
	// the max movement speed of this entity

	bool m_bNegMoveOnX;
	// whether the entity wants to move on negative x
	bool m_bNegMoveOnY;
	// whether the entity wants to move on negative y
	bool m_bPosMoveOnX;
	// whether the entity wants to move on positive x
	bool m_bPosMoveOnY;
	// whether the entity wants to move on positive y

	int m_nLastUpdateTime;
	// last time the entity was updated
	int m_nLastMoveTime;
	// last time that the entity got a movement (they should get a movement speed times per second)

};

#endif