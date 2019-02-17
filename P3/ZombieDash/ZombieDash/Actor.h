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

class Penelope : public Actor
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

private:
	int m_supplyLandmines;
	int m_supplyFlamethrower;
	int m_supplyVaccines;
	bool m_isInfected;
	int m_infectedCount;
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
private:
};

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
