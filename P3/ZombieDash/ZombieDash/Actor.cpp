#include "Actor.h"
#include "StudentWorld.h"

//==============================================ACTORS's IMPLEMENTATIONS=============================================

Actor::Actor(int imageID, double startX, double startY, int depth, StudentWorld* world) : GraphObject(imageID,startX,startY,right,depth), m_isDead(false), m_world(world) {}

bool Actor::isDead()
{
	return m_isDead;
}

void Actor::setDead()
{
	m_isDead = true;
}

StudentWorld* Actor::getWorld()
{
	return m_world;
}

//==============================================PENELOPE's IMPLEMENTATIONS===========================================

//constructor
Penelope::Penelope(double startX, double startY, StudentWorld* world) : Actor(IID_PLAYER, startX, startY,0,world)
{
	m_supplyLandmines = 0;
	m_supplyFlamethrower = 0;
	m_supplyVaccines = 0;
	m_isInfected = false;
	m_infectedCount = 0;
}

//accessor function implementations
/*int Penelope::getSupplyLandmines()
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
}*/

//other function implementations
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
	
	int ch;
	if (getWorld()->getKey(ch))
	{
		switch (ch)
		{
		case KEY_PRESS_LEFT:
		{
			setDirection(left);

			double dest_x = getX() - 4;
			double dest_y = getY();

			//if not out of bounds,

			//NEED TO STILL CHECK FOR BEING OUT OF BOUNDS

			moveTo(getX() - 4, getY());
			break;
		}
		case KEY_PRESS_RIGHT:
		{
			setDirection(right);
			moveTo(getX() + 4, getY());
			break;
		}
		case KEY_PRESS_UP:
		{
			setDirection(up);
			moveTo(getX(), getY() + 4);
			break;
		}
		case KEY_PRESS_DOWN:
		{
			setDirection(down);
			moveTo(getX(), getY() - 4);
			break;
		}
		case KEY_PRESS_SPACE:
		{
			if (m_supplyFlamethrower > 0)
			{
				m_supplyFlamethrower--;
				//play SOUND_PLAYER_FIRE sound effect

				//Introduce three new flame objects into the game in front  of me
			}

			break;
		}
		case KEY_PRESS_TAB:
		{
			if (m_supplyLandmines > 0)
			{
				m_supplyLandmines--;

				//Introduce landmine object on ground into the game
			}

			break;
		}
		case KEY_PRESS_ENTER:
		{
			if (m_supplyVaccines > 0)
			{
				m_supplyVaccines--;

				m_isInfected = false;
				//m_infectedCount = 0;
			}

			break;
		}
		}
	}
}

//==============================================WALL's IMPLEMENTATIONS===============================================

Wall::Wall(double startX, double startY, StudentWorld* world) : Actor(IID_WALL, startX, startY,0, world) {}

void Wall::doSomething() {}
