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

	void finishLevel();

	int getNumCitizensLeft();
	int decNumCitizensLeft();
	Actor* getPlayer();

	bool checkBoundaryAt(double dest_x, double dest_y, Actor* src);
	bool checkOverlapWith(double curr_x, double curr_y, std::string type, Actor* &overlapped);
	bool findNearest(double dest_x, double dest_y, std::string type, double &distance, Actor* nearest);
	Actor* createActor(Level::MazeEntry ge, double startX, double startY);
	Actor* createActor(string type, double startX, double startY, int direction);

	void activateAllActors();

	void infectAllOverlapping(Actor* src);

private:
	list<Actor*> m_actorList;
	Penelope* m_player;
	int m_activeActors;
	int m_numCitizensLeft;
	bool m_finishedLevel;
};

#endif // STUDENTWORLD_H_
