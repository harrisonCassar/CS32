#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include <string>

class StudentWorld;

class Actor : public GraphObject
{
public:
	Actor(int imageID, double startX, double startY, int direction, int depth, StudentWorld* world);
	bool isDead();
	void setDead();
	
	bool isInfected();
	bool setInfected(bool value);
	virtual bool isInfectable(); //RECENTLY ADDED

	bool isActive();
	bool setActive(bool value);

	virtual bool isDamageable();
	virtual void killByFire();
	virtual void killByPit(); //======maybe can combine killByFire and killByPit
	
	virtual bool blocksMovement();
	virtual bool blocksFire();
	
	int getLifeTicks();
	int setLifeTicks(int value);

	StudentWorld* getWorld();
	virtual void doSomething() = 0;

private:
	StudentWorld* m_world;
	
	bool m_isDead;
	bool m_isActive;
	int m_lifeTicks;
	bool m_isInfected;
};

class Character : public Actor
{
public:
	Character(int imageID, double startX, double startY, int depth, StudentWorld* world);
	bool isParalyzed();
	bool setParalyzed(bool value);
	int getInfectedCount();  //RECENTLY MOVED HERE
	int setInfectedCount(int value);  //RECENTLY MOVED HERE

	virtual bool blocksMovement();
	virtual bool isDamageable();
private:
	bool m_isParalyzed;
	int m_infectedCount; //RECENTLY MOVED HERE
};

class Penelope : public Character
{
public:
	Penelope(double startX, double startY, StudentWorld* world);
	virtual void doSomething();

	virtual bool isInfectable(); //RECENTLY ADDED

	//accessor functions
	int getSupplyLandmines();
	int getSupplyFlamethrower();
	int getSupplyVaccines();

	int incSupplyLandmines(int amount);
	int incSupplyFlamethrower(int amount);
	int incSupplyVaccines(int amount);

private:
	int m_supplyLandmines;
	int m_supplyFlamethrower;
	int m_supplyVaccines;
};

class Wall : public Actor
{
public:
	Wall(double startX, double startY, StudentWorld* world);
	virtual void doSomething();
	virtual bool blocksMovement();
	virtual bool blocksFire();
};

class Exit : public Actor
{
public:
	Exit(double startX, double startY, StudentWorld* world);
	virtual void doSomething();
	virtual bool blocksFire();
};

class Citizen : public Character
{
public:
	Citizen(double startX, double startY, StudentWorld* world);
	virtual void doSomething();
	virtual bool isInfectable(); //RECENTLY ADDED
private:
};

class Zombie : public Character
{
public:
	Zombie(double startX, double startY, StudentWorld* world);
	virtual void doSomething() = 0;
	int getMovementPlan();
	int setMovementPlan(int value);
	int decMovementPlan();
private:
	int m_movementPlan;
};

class DumbZombie : public Zombie
{
public:
	DumbZombie(double startX, double startY, StudentWorld* world);
	virtual void doSomething();
};

class SmartZombie : public Zombie
{
public:
	SmartZombie(double startX, double startY, StudentWorld* world);
	virtual void doSomething();
};

class Vomit : public Actor
{
public:
	Vomit(double startX, double startY, int direction, StudentWorld* world);
	virtual void doSomething();
};

class Flame : public Actor
{
public:
	Flame(double startX, double startY, int direction, StudentWorld* world);
	virtual void doSomething();
};

class Pit : public Actor
{
public:
	Pit(double startX, double startY, StudentWorld* world);
	virtual void doSomething();
};

class Goodie : public Actor
{
public:
	Goodie(int imageID, double startX, double startY, StudentWorld* world);
	virtual void doSomething();
	virtual void updateSupply() = 0;
	virtual bool isDamageable();
};

class VaccineGoodie : public Goodie
{
public:
	VaccineGoodie(double startX, double startY, StudentWorld* world);
	virtual void updateSupply();
};

class GasCanGoodie : public Goodie
{
public:
	GasCanGoodie(double startX, double startY, StudentWorld* world);
	virtual void updateSupply();
};

class LandmineGoodie : public Goodie
{
public:
	LandmineGoodie(double startX, double startY, StudentWorld* world);
	virtual void updateSupply();
};

class Landmine : public Actor
{
public:
	Landmine(double startX, double startY, StudentWorld* world);
	virtual void doSomething();
	bool isOnSafety();
private:
	int m_safetyTicks;
};

#endif // ACTOR_H_
