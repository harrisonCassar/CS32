#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include <string>

class StudentWorld;

class Actor : public GraphObject
{
public:
	Actor(int imageID, double startX, double startY, int direction, int depth, StudentWorld* world, std::string type);
	bool isDead();
	void setDead();
	bool isInfected();
	bool setInfected(bool value);
	bool isActive();
	bool setActive(bool value);
	int getInfectedCount();
	int incInfectedCount();
	std::string getType();
	StudentWorld* getWorld();
	virtual void doSomething() = 0;
private:
	std::string m_type;
	bool m_isDead;
	bool m_isActive;
	bool m_isInfected;
	int m_infectedCount;
	StudentWorld* m_world;
};

class Character : public Actor
{
public:
	Character(int imageID, double startX, double startY, int depth, StudentWorld* world, std::string type);
	bool isParalyzed();
	bool setParalyzed(bool value);
	
private:
	bool m_isParalyzed;
};

class Penelope : public Character
{
public:
	Penelope(double startX, double startY, StudentWorld* world);
	virtual void doSomething();

	//accessor functions
	//int getSupplyLandmines();
	//int getSupplyFlamethrower();
	//int getSupplyVaccines();
	//int getInfectedCount();
	//bool isInfected();

	//int incSupplyVaccines();

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
};

class Exit : public Actor
{
public:
	Exit(double startX, double startY, StudentWorld* world);
	virtual void doSomething();
};

class Citizen : public Character
{
public:
	Citizen(double startX, double startY, StudentWorld* world);
	virtual void doSomething();
private:
};

class Zombie : public Character
{
public:
	Zombie(double startX, double startY, StudentWorld* world, std::string type);
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
private:
	int m_lifeTicks;
};



// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
