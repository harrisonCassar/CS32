#include "Actor.h"
#include "StudentWorld.h"
#include <string>

//==============================================ACTORS's IMPLEMENTATIONS=============================================

Actor::Actor(int imageID, double startX, double startY, int depth, StudentWorld* world, std::string type) : GraphObject(imageID, startX, startY, right, depth), m_isDead(false), m_world(world), m_type(type) {}

bool Actor::isDead()
{
	return m_isDead;
}

void Actor::setDead()
{
	m_isDead = true;
}

std::string Actor::getType()
{
	return m_type;
}

StudentWorld* Actor::getWorld()
{
	return m_world;
}

//==============================================PENELOPE's IMPLEMENTATIONS===========================================

//constructor
Penelope::Penelope(double startX, double startY, StudentWorld* world) : Actor(IID_PLAYER, startX, startY,0,world, "Penelope")
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
			getWorld()->playSound(SOUND_PLAYER_DIE);
			return; //MAKE SURE THAT STUDENT WORLD THEN IMMEDIATELY STOPS DOING ANYTHING DURING THE TICK AND ENDS THE LEVEL
		}
	}
	
	int ch;
	if (getWorld()->getKey(ch))
	{
		switch (ch)
		{
		case KEY_PRESS_LEFT:
			setDirection(left);

			if (!getWorld()->checkBoundaryAt(getX() - 4, getY(), this))
			{
				moveTo(getX() - 4, getY());
			}

			break;

		case KEY_PRESS_RIGHT:
			setDirection(right);

			if (!getWorld()->checkBoundaryAt(getX() + 4, getY(), this))
			{
				moveTo(getX() + 4, getY());
			}

			break;

		case KEY_PRESS_UP:
			setDirection(up);

			if (!getWorld()->checkBoundaryAt(getX(), getY() + 4, this))
			{
				moveTo(getX(), getY() + 4);
			}

			break;

		case KEY_PRESS_DOWN:
			setDirection(down);

			if (!getWorld()->checkBoundaryAt(getX(), getY() - 4, this))
			{
				moveTo(getX(), getY() - 4);
			}

			break;

		case KEY_PRESS_SPACE:
			if (m_supplyFlamethrower > 0)
			{
				m_supplyFlamethrower--;
				getWorld()->playSound(SOUND_PLAYER_FIRE);

				//Introduce three new flame objects into the game in front  of me
			}

			break;

		case KEY_PRESS_TAB:
			if (m_supplyLandmines > 0)
			{
				m_supplyLandmines--;

				//Introduce landmine object on ground into the game
			}

			break;

		case KEY_PRESS_ENTER:
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

//==============================================WALL's IMPLEMENTATIONS===============================================

Wall::Wall(double startX, double startY, StudentWorld* world) : Actor(IID_WALL, startX, startY, 0, world, "Wall") {}

void Wall::doSomething() {}

//==============================================EXIT's IMPLEMENTATIONS===============================================

Exit::Exit(double startX, double startY, StudentWorld* world) : Actor(IID_EXIT, startX, startY, 1, world, "Exit") {}

void Exit::doSomething()
{
	Actor* temp = nullptr;
	if (getWorld()->checkOverlapWith(getX(), getY(), "Citizen", temp))
	{
		getWorld()->increaseScore(500);
	
		temp->setDead();

		getWorld()->playSound(SOUND_CITIZEN_SAVED);
	}

	else if (getWorld()->checkOverlapWith(getX(), getY(), "Penelope", temp) && getWorld()->getNumCitizensLeft() == 0)
	{
		getWorld()->finishLevel();
	}
}


