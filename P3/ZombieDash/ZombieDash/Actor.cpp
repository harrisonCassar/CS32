#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <cmath>

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

//==============================================Characters's IMPLEMENTATIONS===========================================
Character::Character(int imageID, double startX, double startY, int depth, StudentWorld* world, std::string type) : Actor(imageID, startX, startY, 0, world, type)
{
	m_isParalyzed = false;
	m_isInfected = false;
	m_infectedCount = 0;
}

bool Character::isInfected()
{
	return m_isInfected;
}


int Character::getInfectedCount()
{
	return m_infectedCount;
}

int Character::incInfectedCount()
{
	return ++m_infectedCount;
}

bool Character::setInfected(bool value)
{
	return m_isInfected = value;
}

bool Character::isParalyzed()
{
	return m_isParalyzed;
}

bool Character::setParalyzed(bool value)
{
	m_isParalyzed = value;
}

//==============================================PENELOPE's IMPLEMENTATIONS===========================================

//constructor
Penelope::Penelope(double startX, double startY, StudentWorld* world) : Character(IID_PLAYER, startX, startY,0,world, "Penelope")
{
	m_supplyLandmines = 0;
	m_supplyFlamethrower = 0;
	m_supplyVaccines = 0;
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

	if (isInfected())
	{
		if (incInfectedCount() >= 500)
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

				setInfected(false);
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

//==============================================CITIZEN's IMPLEMENTATIONS===============================================

Citizen::Citizen(double startX, double startY, StudentWorld* world) : Character(IID_CITIZEN, startX, startY, 0, world, "Citizen") {}

void Citizen::doSomething()
{
	if (isDead())
	{
		getWorld()->playSound(SOUND_CITIZEN_DIE);
		getWorld()->increaseScore(-1000);
		return;
	}

	if (isInfected())
	{
		if (incInfectedCount() >= 500)
		{
			setDead();
			getWorld()->playSound(SOUND_ZOMBIE_BORN);

			getWorld()->increaseScore(-1000);

			//introduce new Zombie (70% dumb, 30% smart)

			return;
		}
	}

	if (isParalyzed())
	{
		setParalyzed(false);
		return;
	}
	else
		setParalyzed(true);

	double dist_p = -1;
	double dist_z = -1;

	getWorld()->findNearest(getX(), getY(), "Penelope", dist_p);
	getWorld()->findNearest(getX(), getY(), "Zombie", dist_z);
	
	if (((dist_z == -1) || (dist_p < dist_z)) && dist_p <= 80 * 80)
	{
		double p_x = getWorld()->getPlayer()->getX();
		double p_y = getWorld()->getPlayer()->getY();

		//if same col || same row
		if (p_y == getY())
		{
			if (p_x > getX() && !getWorld()->checkBoundaryAt(getX() + 2, getY(), this))
			{
				setDirection(right);
				moveTo(getX()+2, getY());
				return;
			}
			else if (p_x < getX() && !getWorld()->checkBoundaryAt(getX() - 2, getY(), this))
			{
				setDirection(left);
				moveTo(getX() - 2, getY());
				return;
			}
			else
				return;
		}
		else if (p_x == getX())
		{
			if (p_y > getY() && !getWorld()->checkBoundaryAt(getX(), getY() + 2, this))
			{
				setDirection(up);
				moveTo(getX(), getY() + 2);
				return;
			}
			else if (p_y < getY() && !getWorld()->checkBoundaryAt(getX(), getY() - 2, this))
			{
				setDirection(down);
				moveTo(getX(), getY() - 2);
				return;
			}
			else
				return;
		}

		//if not same col/row
		else 
		{
			int horizontalDir;
			int verticalDir;
			int firstDir;
			int secondDir;

			if (p_x > getX())
				horizontalDir = right;
			else if (p_x <= getX())
				horizontalDir = left;

			if (p_y > getY())
				verticalDir = up;
			else if (p_y <= getY())
				verticalDir = down;

			if (randInt(1, 2) == 1)
			{
				firstDir = verticalDir;
				secondDir = horizontalDir;
			}
			else
			{
				firstDir = horizontalDir;
				secondDir = verticalDir;
			}

			//check first direction
			if (firstDir == up && !(getWorld()->checkBoundaryAt(getX(), getY() + 2, this)))
			{
				setDirection(up);
				moveTo(getX(), getY() + 2);
				return;
			}
			if (firstDir == down && !(getWorld()->checkBoundaryAt(getX(), getY() - 2, this)))
			{
				setDirection(down);
				moveTo(getX(), getY() - 2);
				return;
			}
			if (firstDir == left && !(getWorld()->checkBoundaryAt(getX() - 2, getY(), this)))
			{
				setDirection(left);
				moveTo(getX() - 2, getY());
				return;
			}
			if (firstDir == right && !(getWorld()->checkBoundaryAt(getX() + 2, getY(), this)))
			{
				setDirection(right);
				moveTo(getX() + 2, getY());
				return;
			}

			//check second direction
			if (secondDir == up && !(getWorld()->checkBoundaryAt(getX(), getY() + 2, this)))
			{
				setDirection(up);
				moveTo(getX(), getY() + 2);
				return;
			}
			if (secondDir == down && !(getWorld()->checkBoundaryAt(getX(), getY() - 2, this)))
			{
				setDirection(down);
				moveTo(getX(), getY() - 2);
				return;
			}
			if (secondDir == left && !(getWorld()->checkBoundaryAt(getX() - 2, getY(), this)))
			{
				setDirection(left);
				moveTo(getX() - 2, getY());
				return;
			}
			if (secondDir == right && !(getWorld()->checkBoundaryAt(getX() + 2, getY(), this)))
			{
				setDirection(right);
				moveTo(getX() + 2, getY());
				return;
			}
		}
	}
	
	//if a zombie is too close, run away
	if (dist_z != -1 && dist_z <= 80 * 80)
	{
		double dist_near = dist_z;
		int bestDir = -1;

		//check for block/potential movement in each direction
		if (!(getWorld()->checkBoundaryAt(getX(), getY() + 2, this)))
		{
			double dist_candidate;
			getWorld()->findNearest(getX(), getY() + 2, "Zombie", dist_candidate);
			if (dist_candidate < dist_near)
			{
				dist_near = dist_candidate;
				bestDir = up;
			}
		}
		if (!(getWorld()->checkBoundaryAt(getX(), getY() - 2, this)))
		{
			double dist_candidate;
			getWorld()->findNearest(getX(), getY() - 2, "Zombie", dist_candidate);
			if (dist_candidate < dist_near)
			{
				dist_near = dist_candidate;
				bestDir = down;
			}
		}
		if (!(getWorld()->checkBoundaryAt(getX() + 2, getY(), this)))
		{
			double dist_candidate;
			getWorld()->findNearest(getX() + 2, getY(), "Zombie", dist_candidate);
			if (dist_candidate < dist_near)
			{
				dist_near = dist_candidate;
				bestDir = right;
			}
		}
		if (!(getWorld()->checkBoundaryAt(getX() - 2, getY(), this)))
		{
			double dist_candidate;
			getWorld()->findNearest(getX() - 2, getY(), "Zombie", dist_candidate);
			if (dist_candidate < dist_near)
			{
				dist_near = dist_candidate;
				bestDir = left;
			}
		}

		if (bestDir == -1)
		{
			cerr << "No good direction for me, the Citizen!" << endl;
			return;
		}
		
		setDirection(bestDir);

		if (bestDir == up)
			moveTo(getX(), getY() + 2);
		else if (bestDir == down)
			moveTo(getX(), getY() - 2);
		else if (bestDir == left)
			moveTo(getX() - 2, getY());
		else if (bestDir == right)
			moveTo(getX() + 2, getY());

		return;
	}
}

//==============================================ZOMBIE's IMPLEMENTATIONS===============================================

Zombie::Zombie(double startX, double startY, StudentWorld* world, string type) : Character(IID_ZOMBIE, startX, startY, 0, world, type), m_movementPlanDist(0) {}

//============================================DUMB ZOMBIE's IMPLEMENTATIONS===============================================

DumbZombie::DumbZombie(double startX, double startY, StudentWorld* world) : Zombie(startX, startY, world, "DumbZombie") {}

void DumbZombie::doSomething()
{
	if (isDead())
		return;

	if (isParalyzed())
	{
		setParalyzed(false);
		return;
	}
	else
		setParalyzed(true);

	double curr_x = getX();
	double curr_y = getY();

	double vomit_x;
	double vomit_y;

	int dir = getDirection();

	switch (dir)
	{
	case up:
		vomit_x = curr_x;
		vomit_y = curr_y + SPRITE_HEIGHT;
		break;
	case down:
		vomit_x = curr_x;
		vomit_y = curr_y - SPRITE_HEIGHT;
		break;
	case left:
		vomit_x = curr_x - SPRITE_HEIGHT;
		vomit_y = curr_y;
		break;
	case right:
		vomit_x = curr_x + SPRITE_HEIGHT;
		vomit_y = curr_y;
		break;
	}

	Actor* overlapped = nullptr;

	if (getWorld()->checkOverlapWith(vomit_x, vomit_y, "Penelope", overlapped) || getWorld()->checkOverlapWith(vomit_x,vomit_y, "Citizen", overlapped))
	{
		if (randInt(1, 3) == 1)
		{
			getWorld()->createActor("Vomit", vomit_x, vomit_y));
			getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
			return;
		}
	}


}

//===========================================SMART ZOMBIE's IMPLEMENTATIONS===============================================