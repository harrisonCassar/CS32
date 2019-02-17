#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

#include "GameWorld.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <list>
using namespace std;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
	virtual ~StudentWorld();
    
	virtual int init();
    virtual int move();
    virtual void cleanUp();

	bool checkBoundary(double dest_x, double dest_y);
	
private:
	Actor* createActor(Level::MazeEntry ge, double startX, double startY);

	list<Actor*> m_actorList;
	Penelope* m_player;
	int m_numCitizensLeft;
};

#endif // STUDENTWORLD_H_
