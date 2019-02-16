#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"

class Actor : public GraphObject
{
public:
	Actor(int imageID, double startX, double startY);
	bool isDead();
	void setDead();
	virtual void doSomething() = 0;
private:
	bool m_isDead;
	//m_direction;
	//m_depth;
};

class Penelope : public Actor
{
public:
	Penelope(double startX, double startY);
	virtual void setKeyPressed(int newKey);
	virtual void doSomething();

	//accessor functions
	int getKeyPressed();
	int getSupplyLandmines();
	int getSupplyFlamethrower();
	int getSupplyVaccines();
	int getInfectedCount();
	bool isInfected();

private:
	int m_keyPressed;
	int m_supplyLandmines;
	int m_supplyFlamethrower;
	int m_supplyVaccines;
	bool m_isInfected;
	int m_infectedCount;
};

class Wall : public Actor
{
public:
	Wall(double startX, double startY);
	virtual void doSomething();
private:
};

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
