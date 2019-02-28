#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <cmath>

//==============================================ACTORS's IMPLEMENTATIONS=============================================

Actor::Actor(int imageID, double startX, double startY, int direction, int depth, StudentWorld* world) : GraphObject(imageID, startX, startY, direction, depth), m_world(world), m_isDead(false), m_isActive(false), m_isInfected(false), m_lifeTicks(0) {}

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

bool Actor::isInfected()
{
	return m_isInfected;
}

bool Actor::setInfected(bool value)
{
	return m_isInfected = value;
}

bool Actor::isInfectable()
{
	return false;
}

bool Actor::isActive()
{
	return m_isActive;
}

bool Actor::setActive(bool value)
{
	return m_isActive = value;
}

bool Actor::isDamageable()
{
	return false;
}

void Actor::killByHazard() //======maybe can combine killByFire and killByPit
{
	return;
}

bool Actor::blocksMovement()
{
	return false;
}

bool Actor::blocksFire()
{
	return false;
}

bool Actor::isFriendly()
{
	return false;
}

bool Actor::isEvil()
{
	return false;
}

bool Actor::canPickUp()
{
	return false;
}

bool Actor::canActivateTraps()
{
	return false;
}

int Actor::getLifeTicks()
{
	return m_lifeTicks;
}

int Actor::setLifeTicks(int value)
{
	return m_lifeTicks = value;
}

bool Actor::isSavable()
{
	return false;
}

//==============================================Characters's IMPLEMENTATIONS===========================================
Character::Character(int imageID, double startX, double startY, StudentWorld* world) : Actor(imageID, startX, startY, right, 0, world), m_isParalyzed(false), m_infectedCount(0) {}

bool Character::isParalyzed()
{
	return m_isParalyzed;
}

bool Character::setParalyzed(bool value)
{
	return m_isParalyzed = value;
}

int Character::getInfectedCount()
{
	return m_infectedCount;
}

int Character::setInfectedCount(int value)
{
	return m_infectedCount = value;
}

bool Character::blocksMovement()
{
	return true;
}

bool Character::isDamageable()
{
	return true;
}

bool Character::canActivateTraps()
{
	return true;
}

//==============================================PENELOPE's IMPLEMENTATIONS===========================================

Penelope::Penelope(double startX, double startY, StudentWorld* world) : Character(IID_PLAYER, startX, startY,world)
{
	m_supplyLandmines = 0;
	m_supplyFlamethrower = 0;
	m_supplyVaccines = 0;
}

bool Penelope::isInfectable()
{
	return true;
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

int Penelope::incSupplyLandmines(int amount)
{
	return m_supplyLandmines += amount;
}

int Penelope::incSupplyFlamethrower(int amount)
{
	return m_supplyFlamethrower += amount;
}

int Penelope::incSupplyVaccines(int amount)
{
	return m_supplyVaccines += amount;
}

void Penelope::killByHazard() //======maybe can combine killByFire and killByPit
{
	setDead();
}

bool Penelope::isFriendly()
{
	return true;
}

bool Penelope::canPickUp()
{
	return true;
}

void Penelope::doSomething()
{
	if (isDead())
		return;

	if (isInfected())
	{
		if (setInfectedCount(getInfectedCount()+1) >= 500)
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
				for (int i = 1; i < 4; i++)
				{
					double pos_x;
					double pos_y;

					if (getDirection() == up)
					{
						pos_x = getX();
						pos_y = getY() + (i*SPRITE_HEIGHT);
					}
					else if (getDirection() == down)
					{
						pos_x = getX();
						pos_y = getY() - (i*SPRITE_HEIGHT);
					}
					else if (getDirection() == left)
					{
						pos_x = getX() - (i*SPRITE_WIDTH);
						pos_y = getY();
					}
					else if (getDirection() == right)
					{
						pos_x = getX() + (i*SPRITE_WIDTH);
						pos_y = getY();
					}

					if (getWorld()->checkOverlapWithBlocksFire(pos_x, pos_y))
						break;
					else
						getWorld()->addActor(new Flame(pos_x, pos_y, getDirection(),getWorld()));
				}
			}

			break;

		case KEY_PRESS_TAB:
			if (m_supplyLandmines > 0)
			{
				m_supplyLandmines--;

				//Introduce landmine object on ground into the game
				getWorld()->addActor(new Landmine(getX(), getY(), getWorld()));
			}

			break;

		case KEY_PRESS_ENTER:
			if (m_supplyVaccines > 0)
			{
				m_supplyVaccines--;

				setInfected(false);
				setInfectedCount(0);
			}

			break;
		}
	}
}

//==============================================WALL's IMPLEMENTATIONS===============================================

Wall::Wall(double startX, double startY, StudentWorld* world) : Actor(IID_WALL, startX, startY, right, 0, world) {}

void Wall::doSomething() {}

bool Wall::blocksMovement()
{
	return true;
}

bool Wall::blocksFire()
{
	return true;
}

//==============================================EXIT's IMPLEMENTATIONS===============================================

Exit::Exit(double startX, double startY, StudentWorld* world) : Actor(IID_EXIT, startX, startY, right, 1, world) {}

void Exit::doSomething()
{
	Actor* temp = nullptr;

	if (getWorld()->getNumCitizensLeft() != 0 && getWorld()->checkOverlapWithSavable(this, temp))
	{
		getWorld()->increaseScore(500);

		temp->setDead();

		getWorld()->playSound(SOUND_CITIZEN_SAVED);

		getWorld()->decNumCitizensLeft();
	}
	else if (getWorld()->getNumCitizensLeft() == 0 && getWorld()->checkOverlap(this, getWorld()->getPlayer()))
	{
		getWorld()->finishLevel();
		getWorld()->playSound(SOUND_LEVEL_FINISHED);
	}
}

bool Exit::blocksFire()
{
	return true;
}

//==============================================CITIZEN's IMPLEMENTATIONS===============================================

Citizen::Citizen(double startX, double startY, StudentWorld* world) : Character(IID_CITIZEN, startX, startY, world) {}

void Citizen::doSomething()
{
	if (isDead())
	{
		return;
	}

	if (isInfected())
	{
		if (setInfectedCount(getInfectedCount()+1) >= 500)
		{
			setDead();
			getWorld()->playSound(SOUND_ZOMBIE_BORN);
			getWorld()->decNumCitizensLeft();
			getWorld()->increaseScore(-1000);

			//introduce new Zombie (70% dumb, 30% smart)
			if (randInt(1, 10) <= 7)
			{
				getWorld()->addActor(new DumbZombie(getX(), getY(), getWorld()));
				cerr << "Created DumbZombie" << endl;
			}
			else
			{
				getWorld()->addActor(new SmartZombie(getX(), getY(), getWorld()));
				cerr << "Created SmartZombie" << endl;
			}

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

	Actor* throwaway = nullptr;

	getWorld()->findNearestPlayer(getX(), getY(), dist_p, throwaway);
	getWorld()->findNearestEvil(getX(), getY(), dist_z, throwaway);
	
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
			getWorld()->findNearestEvil(getX(), getY() + 2, dist_candidate, throwaway);
			if (dist_candidate > dist_near)
			{
				dist_near = dist_candidate;
				bestDir = up;
			}
		}
		if (!(getWorld()->checkBoundaryAt(getX(), getY() - 2, this)))
		{
			double dist_candidate;
			getWorld()->findNearestEvil(getX(), getY() - 2, dist_candidate, throwaway);
			if (dist_candidate > dist_near)
			{
				dist_near = dist_candidate;
				bestDir = down;
			}
		}
		if (!(getWorld()->checkBoundaryAt(getX() + 2, getY(), this)))
		{
			double dist_candidate;
			getWorld()->findNearestEvil(getX() + 2, getY(), dist_candidate, throwaway);
			if (dist_candidate > dist_near)
			{
				dist_near = dist_candidate;
				bestDir = right;
			}
		}
		if (!(getWorld()->checkBoundaryAt(getX() - 2, getY(), this)))
		{
			double dist_candidate;
			getWorld()->findNearestEvil(getX() - 2, getY(), dist_candidate, throwaway);
			if (dist_candidate > dist_near)
			{
				dist_near = dist_candidate;
				bestDir = left;
			}
		}

		if (bestDir == -1)
		{
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

bool Citizen::isInfectable()
{
	return true;
}

void Citizen::killByHazard() //======maybe can combine killByFire and killByPit
{
	setDead();
	getWorld()->playSound(SOUND_CITIZEN_DIE);
	getWorld()->increaseScore(-1000);
	getWorld()->decNumCitizensLeft();
}

bool Citizen::isFriendly()
{
	return true;
}

bool Citizen::isSavable()
{
	return true;
}

//==============================================ZOMBIE's IMPLEMENTATIONS===============================================

Zombie::Zombie(double startX, double startY, StudentWorld* world) : Character(IID_ZOMBIE, startX, startY, world), m_movementPlan(0) {}

int Zombie::getMovementPlan()
{
	return m_movementPlan;
}

int Zombie::setMovementPlan(int value)
{
	return m_movementPlan = value;
}

int Zombie::decMovementPlan()
{
	return --m_movementPlan;
}

bool Zombie::isEvil()
{
	return true;
}

//============================================DUMB ZOMBIE's IMPLEMENTATIONS===============================================

DumbZombie::DumbZombie(double startX, double startY, StudentWorld* world) : Zombie(startX, startY, world) {}

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
		vomit_x = curr_x - SPRITE_WIDTH;
		vomit_y = curr_y;
		break;
	case right:
		vomit_x = curr_x + SPRITE_WIDTH;
		vomit_y = curr_y;
		break;
	}

	if (getWorld()->checkOverlapWithInfectable(vomit_x, vomit_y))
	{
		if (randInt(1, 3) == 1)
		{
			getWorld()->addActor(new Vomit(vomit_x, vomit_y, dir, getWorld()));
			getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
			return;
		}
	}

	if (getMovementPlan() == 0)
	{
		setMovementPlan(randInt(3, 10));

		switch (randInt(1, 4))
		{
		case 1:
			setDirection(up);
			break;
		case 2:
			setDirection(down);
			break;
		case 3:
			setDirection(left);
			break;
		case 4:
			setDirection(right);
			break;
		}
	}

	double dest_x;
	double dest_y;

	if (getDirection() == up)
	{
		dest_x = getX();
		dest_y = getY() + 1;
	}
	else if (getDirection() == down)
	{
		dest_x = getX();
		dest_y = getY() - 1;
	}
	else if (getDirection() == left)
	{
		dest_x = getX() - 1;
		dest_y = getY();
	}
	else if (getDirection() == right)
	{
		dest_x = getX() + 1;
		dest_y = getY();
	}

	if (!getWorld()->checkBoundaryAt(dest_x, dest_y, this))
	{
		moveTo(dest_x, dest_y);
		decMovementPlan();
	}
	else
		setMovementPlan(0);
}

void DumbZombie::killByHazard()
{
	setDead();
	getWorld()->playSound(SOUND_ZOMBIE_DIE);
	getWorld()->increaseScore(1000);

	if (randInt(1, 10) == 1)
	{
		double curr_x = getX();
		double curr_y = getY();

		double vaccine_x;
		double vaccine_y;

		switch (randInt(1, 4))
		{
		case 1: //up
			vaccine_x = curr_x;
			vaccine_y = curr_y + SPRITE_HEIGHT;
			break;
		case 2: //down
			vaccine_x = curr_x;
			vaccine_y = curr_y - SPRITE_HEIGHT;
			break;
		case 3: //left
			vaccine_x = curr_x - SPRITE_WIDTH;
			vaccine_y = curr_y;
			break;
		case 4: //right
			vaccine_x = curr_x + SPRITE_WIDTH;
			vaccine_y = curr_y;
			break;
		}

		if (!(getWorld()->checkOverlapWithAny(vaccine_x, vaccine_y)))
		{
			getWorld()->addActor(new VaccineGoodie(vaccine_x, vaccine_y, getWorld()));
		}
	}
}

//===========================================SMART ZOMBIE's IMPLEMENTATIONS===============================================
SmartZombie::SmartZombie(double startX, double startY, StudentWorld* world) : Zombie(startX, startY, world) {}

void SmartZombie::doSomething()
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
		vomit_x = curr_x - SPRITE_WIDTH;
		vomit_y = curr_y;
		break;
	case right:
		vomit_x = curr_x + SPRITE_WIDTH;
		vomit_y = curr_y;
		break;
	}

	if (getWorld()->checkOverlapWithInfectable(vomit_x, vomit_y))
	{
		if (randInt(1, 3) == 1)
		{
			getWorld()->addActor(new Vomit(vomit_x, vomit_y, dir, getWorld()));
			getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
			return;
		}
	}

	if (getMovementPlan() == 0)
	{
		setMovementPlan(randInt(3, 10));

		double p_dist = -1;
		double c_dist = -1;

		double dist;

		Actor* nearest_player = nullptr;
		Actor* nearest_citizen = nullptr;
		Actor* nearest = nullptr;
		getWorld()->findNearestPlayer(getX(), getY(), p_dist, nearest_player);
		if (getWorld()->findNearestFriendly(getX(), getY(), c_dist, nearest_citizen) && c_dist <= p_dist)
		{
			dist = c_dist;
			nearest = nearest_citizen;
		}
		else
		{
			dist = p_dist;
			nearest = nearest_player;
		}

		if (getWorld()->getNumCitizensLeft() == 0)
		{
			dist = p_dist;
			nearest = nearest_player;
		}

		cerr << "p: " << p_dist << " c: " << c_dist << " dist: " << dist << endl;

		if (dist <= 80*80)
		{
			double near_x = nearest->getX();
			double near_y = nearest->getY();
			int horizontalDir;
			int verticalDir;

			//set optimal vertical and horizontal directions
			if (getY() > near_y)
				verticalDir = down;
			else
				verticalDir = up;

			if (getX() > near_x)
				horizontalDir = left;
			else
				horizontalDir = right;
			//set direction if same row/col, or randomly select which optimal direction
			if (getX() == near_x)
			{
				setDirection(verticalDir);
			}
				
			else if (getY() == near_y)
			{
				setDirection(horizontalDir);
			}
				
			else
			{
				if (randInt(1, 2) == 1)
				{
					setDirection(verticalDir);
				}
				else
				{
					setDirection(horizontalDir);
				}
			}
		}
		else
		{
			switch (randInt(1, 4))
			{
			case 1:
				setDirection(up);
				break;
			case 2:
				setDirection(down);
				break;
			case 3:
				setDirection(left);
				break;
			case 4:
				setDirection(right);
				break;
			}
		}
	}

	double dest_x;
	double dest_y;

	if (getDirection() == up)
	{
		dest_x = getX();
		dest_y = getY() + 1;
	}
	else if (getDirection() == down)
	{
		dest_x = getX();
		dest_y = getY() - 1;
	}
	else if (getDirection() == left)
	{
		dest_x = getX() - 1;
		dest_y = getY();
	}
	else if (getDirection() == right)
	{
		dest_x = getX() + 1;
		dest_y = getY();
	}

	if (!getWorld()->checkBoundaryAt(dest_x, dest_y, this))
	{
		moveTo(dest_x, dest_y);
		decMovementPlan();
	}
	else
		setMovementPlan(0);
}

void SmartZombie::killByHazard()
{
	setDead();
	getWorld()->playSound(SOUND_ZOMBIE_DIE);
	getWorld()->increaseScore(2000);
}

//=============================================VOMIT's IMPLEMENTATIONS===============================================
Vomit::Vomit(double startX, double startY, int direction, StudentWorld* world) : Actor(IID_VOMIT, startX, startY, direction, 0, world) {}

void Vomit::doSomething()
{
	if (isDead())
		return;

	if (getLifeTicks() > 2)
	{
		setDead();
		return;
	}
	else
		cerr << setLifeTicks(getLifeTicks()+1) << endl;

	getWorld()->infectAllOverlapping(this);
}

//===============================================FLAME's IMPLEMENTATIONS===============================================
Flame::Flame(double startX, double startY, int direction, StudentWorld* world) : Actor(IID_FLAME, startX, startY, direction, 0, world) {}

void Flame::doSomething()
{
	if (isDead())
		return;

	if (getLifeTicks() > 2)
	{
		setDead();
		return;
	}
	else
		setLifeTicks(getLifeTicks()+1);

	getWorld()->damageAllOverlapping(this);
}

//===============================================PIT's IMPLEMENTATIONS===============================================
Pit::Pit(double startX, double startY, StudentWorld* world) : Actor(IID_PIT, startX, startY, right, 0, world) {}

void Pit::doSomething()
{
	getWorld()->damageAllOverlapping(this);
}

//===============================================GOODIE's IMPLEMENTATIONS===============================================
Goodie::Goodie(int imageID, double startX, double startY, StudentWorld* world) : Actor(imageID, startX, startY, right, 1, world) {}

void Goodie::doSomething()
{
	if (isDead())
		return;

	if (getWorld()->checkOverlapWithCanPickup(this))
	{
		getWorld()->increaseScore(50);

		setDead();

		getWorld()->playSound(SOUND_GOT_GOODIE);

		updateSupply();
	}
}

bool Goodie::isDamageable()
{
	return true;
}

void Goodie::killByHazard()
{
	setDead();
}

//===============================================VACCINE GOODIE's IMPLEMENTATIONS===============================================
VaccineGoodie::VaccineGoodie(double startX, double startY, StudentWorld* world) : Goodie(IID_VACCINE_GOODIE, startX, startY, world) {}

void VaccineGoodie::updateSupply()
{
	getWorld()->updateVaccineSupply(1);
}

//===============================================GAS CAN GOODIE's IMPLEMENTATIONS===============================================
GasCanGoodie::GasCanGoodie(double startX, double startY, StudentWorld* world) : Goodie(IID_GAS_CAN_GOODIE, startX, startY, world) {}

void GasCanGoodie::updateSupply()
{
	getWorld()->updateFlamethrowerSupply(5);
}

//===============================================LANDMINE GOODIE's IMPLEMENTATIONS===============================================
LandmineGoodie::LandmineGoodie(double startX, double startY, StudentWorld* world) : Goodie(IID_LANDMINE_GOODIE, startX, startY, world) {}

void LandmineGoodie::updateSupply()
{
	getWorld()->updateLandmineSupply(2);
}

//==================================================LANDMINE's IMPLEMENTATIONS===============================================
Landmine::Landmine(double startX, double startY, StudentWorld* world) : Actor(IID_LANDMINE, startX, startY, right, 1, world), m_safetyTicks(30) {}

bool Landmine::isOnSafety()
{
	if (m_safetyTicks != 0)
		return true;
	return false;
}

void Landmine::doSomething()
{
	if (isDead())
		return;

	if (isOnSafety())
	{
		m_safetyTicks--;
		return;
	}

	if (getWorld()->checkOverlapWithCanActivateTraps(this))
	{
		killByHazard();
	}
}

void Landmine::killByHazard()
{
	setDead();

	getWorld()->playSound(SOUND_LANDMINE_EXPLODE);

	//introduce flames at and around landmine's position
	if (!getWorld()->checkFireBoundaryAt(getX() - SPRITE_WIDTH, getY() + SPRITE_HEIGHT))
		getWorld()->addActor(new Flame(getX() - SPRITE_WIDTH, getY() + SPRITE_HEIGHT, up, getWorld()));
	if (!getWorld()->checkFireBoundaryAt(getX(), getY() + SPRITE_HEIGHT))
		getWorld()->addActor(new Flame(getX(), getY() + SPRITE_HEIGHT, up, getWorld()));
	if (!getWorld()->checkFireBoundaryAt(getX() + SPRITE_WIDTH, getY() + SPRITE_HEIGHT))
		getWorld()->addActor(new Flame(getX() + SPRITE_WIDTH, getY() + SPRITE_HEIGHT, up, getWorld()));
	if (!getWorld()->checkFireBoundaryAt(getX() - SPRITE_WIDTH, getY()))
		getWorld()->addActor(new Flame(getX() - SPRITE_WIDTH, getY(), up, getWorld()));
	if (!getWorld()->checkFireBoundaryAt(getX(), getY()))
		getWorld()->addActor(new Flame(getX(), getY(), up, getWorld()));
	if (!getWorld()->checkFireBoundaryAt(getX() + SPRITE_WIDTH, getY()))
		getWorld()->addActor(new Flame(getX() + SPRITE_WIDTH, getY(), up, getWorld()));
	if (!getWorld()->checkFireBoundaryAt(getX() - SPRITE_WIDTH, getY() - SPRITE_HEIGHT))
		getWorld()->addActor(new Flame(getX() - SPRITE_WIDTH, getY() - SPRITE_HEIGHT, up, getWorld()));
	if (!getWorld()->checkFireBoundaryAt(getX(), getY() - SPRITE_HEIGHT))
		getWorld()->addActor(new Flame(getX(), getY() - SPRITE_HEIGHT, up, getWorld()));
	if (!getWorld()->checkFireBoundaryAt(getX() + SPRITE_WIDTH, getY() - SPRITE_HEIGHT))
		getWorld()->addActor(new Flame(getX() + SPRITE_WIDTH, getY() - SPRITE_HEIGHT, up, getWorld()));

	//introduce pit at landmine's positon
	getWorld()->addActor(new Pit(getX(), getY(), getWorld()));
}