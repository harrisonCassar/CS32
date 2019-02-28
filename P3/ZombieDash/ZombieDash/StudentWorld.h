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
	bool checkFireBoundaryAt(double dest_x, double dest_y);

	bool checkOverlapWithDamageable(Actor* src, Actor* other);
	bool checkOverlapWithSavable(Actor* src, Actor* &overlapped);
	bool checkOverlapWithCanPickup(Actor* src);
	bool checkOverlapWithCanActivateTraps(Actor* src);
	bool checkOverlapWithInfectable(double x_pos, double y_pos);
	bool checkOverlapWithInfectable(Actor* src, Actor* other);
	bool checkOverlapWithBlocksFire(double x_pos, double y_pos);
	bool checkOverlapWithAny(double x_pos, double y_pos);
	
	bool checkOverlap(Actor* src, Actor* other);
	bool checkOverlap(double x_pos, double y_pos, Actor* other);

	bool findNearestPlayer(double dest_x, double dest_y, double &distance, Actor* &nearest);
	bool findNearestEvil(double dest_x, double dest_y, double &distance, Actor* &nearest);
	bool findNearestFriendly(double dest_x, double dest_y, double &distance, Actor* &nearest); //this does not include checks for Player, even though it is Friendly

	double calculateDistance(double x_src, double y_src, double x_other, double y_other);

	Actor* createActor(Level::MazeEntry ge, double startX, double startY);
	void addActor(Actor* created);

	string updateStatLine();
	void updateVaccineSupply(int value);
	void updateFlamethrowerSupply(int value);
	void updateLandmineSupply(int value);

	void activateAllActors();

	void infectAllOverlapping(Actor* src);
	void damageAllOverlapping(Actor* src);
	
private:
	list<Actor*> m_actorList;
	Penelope* m_player;
	int m_activeActors;
	int m_numCitizensLeft;
	bool m_finishedLevel;
};

#endif // STUDENTWORLD_H_
