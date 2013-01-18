#include ".\person.h"
#include "ZombieGFX.h"

Person::Person(void)
{
	// turn this into a zombie lunch
	m_ThisEntityIs = E_TYPE_PERSON;
}

Person::~Person(void)
{
}

void Person::Draw(ZombieGFX* pGFXManager)
{
	if (pGFXManager)
		pGFXManager->DrawPerson(m_nXPos, m_nYPos);
}

void Person::ResetAI()
{

}