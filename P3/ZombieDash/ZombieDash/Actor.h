#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"

class Actor : public GraphObject
{
public:
	Actor(int imageID, double startX, double startY);
	virtual void doSomething() = 0;
private:
};

class Penelope : public Actor
{
public:
	Penelope();
	virtual void doSomething();
private:
	int m_keyPressed;
};

class Wall : public Actor
{

};

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
