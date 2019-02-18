#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include <string>

class StudentWorld;

class Actor : public GraphObject
{
public:
	Actor(int imageID, double startX, double startY, int depth, StudentWorld* world, std::string type);
	bool isDead();
	void setDead();
	std::string getType();
	StudentWorld* getWorld();
	virtual void doSomething() = 0;
private:
	std::string m_type;
	bool m_isDead;
	StudentWorld* m_world;
};

class Character : public Actor
{
public:
	Character(int imageID, double startX, double startY, int depth, StudentWorld* world, std::string type);
	bool isParalyzed();
	bool setParalyzed(bool value);
	bool isInfected();
	bool setInfected(bool value);
	int getInfectedCount();
	int incInfectedCount();
private:
	bool m_isInfected;
	int m_infectedCount;
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
private:
	int m_movementPlanDist;
};

class DumbZombie : public Zombie
{
public:
	DumbZombie(double startX, double startY, StudentWorld* world);
	virtual void doSomething();
private:
};

class SmartZombie : public Zombie
{
public:
	SmartZombie(double startX, double startY, StudentWorld* world);
	virtual void doSomething();
private:
};



// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
