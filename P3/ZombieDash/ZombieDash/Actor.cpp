#include "Actor.h"
#include "StudentWorld.h"


//==============================================ACTORS's IMPLEMENTATIONS=============================================

Actor::Actor(int imageID, double startX, double startY) : GraphObject(imageID,startX,startY), m_isDead(false) {}

bool Actor::isDead()
{
	return m_isDead;
}

void Actor::setDead()
{
	m_isDead = true;
}

//==============================================PENELOPE's IMPLEMENTATIONS===========================================

//constructor
Penelope::Penelope(double startX, double startY) : Actor(IID_PLAYER, startX, startY)
{
	m_keyPressed = -1;
	m_supplyLandmines = 0;
	m_supplyFlamethrower = 0;
	m_supplyVaccines = 0;
	m_isInfected = false;
	m_infectedCount = 0;
}

//accessor function implementations
int Penelope::getKeyPressed()
{
	return m_keyPressed;
}

int Penelope::getSupplyLandmines()
{
	return m_supplyLandmines;
}

int Penelope::getSupplyFlamethrower()
{
	return m_supplyFlamethrower;
}

int Penelope::getSupplyVaccines()
{
	return m_supplyVaccines;
}

int Penelope::getSupplyLandmines()
{
	return m_supplyLandmines;
}

bool Penelope::isInfected()
{
	return m_isInfected;
}

int Penelope::getInfectedCount()
{
	return m_infectedCount;
}

//other function implementations
void Penelope::setKeyPressed(int newKey)
{
	m_keyPressed = newKey;
}

void Penelope::doSomething()
{
	if (isDead())
		return;

	if (m_isInfected)
	{
		if (++m_infectedCount >= 500)
		{
			setDead();
			//play SOUND_PLAYER_DIE sound effect
			return; //MAKE SURE THAT STUDENT WORLD THEN IMMEDIATELY STOPS DOING ANYTHING DURING THE TICK AND ENDS THE LEVEL
		}
	}
	
	if (m_keyPressed != -1)
	{
		switch (m_keyPressed)
		{
		case KEY_PRESS_LEFT:

		case KEY_PRESS_RIGHT:
		case KEY_PRESS_UP:
		case KEY_PRESS_DOWN:
		case KEY_PRESS_SPACE:
		case KEY_PRESS_TAB:
		case KEY_PRESS_ENTER:
		}




		If the user pressed the UP key then
		Increase my y location by one
		If the user pressed the DOWN key then
		Decrease my y location by one
		...
		If the user pressed the space bar to fire and I have flamethrower charges left, then
		Introduce three new flame objects into the game in front  of me
		...
}
...
 };

//==============================================WALL's IMPLEMENTATIONS===============================================

Wall::Wall(double startX, double startY) : Actor(IID_WALL, startX, startY) {}

