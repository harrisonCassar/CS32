#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

#include "GameWorld.h"
#include "Level.h"
#include <string>
#include <list>
using namespace std;

//declare Actor class's existence
class Actor;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
	virtual ~StudentWorld();
    
	virtual int init();
    virtual int move();
    virtual void cleanUp();
	
private:
	Actor* createActor(Level::MazeEntry ge);

	list<Actor*> m_actorList;
	Actor* m_player;
	int m_numCitizensLeft;
};

#endif // STUDENTWORLD_H_
