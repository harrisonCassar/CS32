#include "StudentWorld.h"
#include "GameConstants.h"
#include <iostream> // defines the overloads of the << operator
#include <sstream>
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

StudentWorld::~StudentWorld()
{
}

int StudentWorld::init()
{
	//construct new level object
	Level lev(assetPath());

	//construct path for current level
	ostringstream oss;
	oss.setf(ios::fixed);
	oss.precision(2);\

	oss << "level";
	if (getLevel() < 10)
		oss << "0";

	oss << getLevel() << ".txt";

	string levelFile = oss.str();
	
	//load level, check for errors, and traverse through entire file, creating respective indicated Actor objects
	Level::LoadResult result = lev.loadLevel(levelFile);
	if (result == Level::load_fail_file_not_found)
		cerr << "Cannot find level01.txt data file" << endl;
	else if (result == Level::load_fail_bad_format)
		cerr << "Your level was improperly formatted" << endl;
	else if (result == Level::load_success)
	{
		cerr << "Successfully loaded level" << endl;

		for (int y = 0; y < LEVEL_HEIGHT; y++)
		{
			for (int x = 0; x < LEVEL_WIDTH; x++)
			{
				Level::MazeEntry ge = lev.getContentsOf(x, y);

				if (ge == Level::player)
					m_player = new Penelope(SPRITE_WIDTH * x, SPRITE_HEIGHT * y);
				else if (ge != Level::empty)
				{
					Actor* temp = createActor(ge,x,y);
					if (temp == nullptr)
						return GWSTATUS_LEVEL_ERROR;

					m_actorList.push_back(temp);
				}
			}
		}
	}
	else
		return GWSTATUS_LEVEL_ERROR;

    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	int value = -1;
	if (getKey(value))
		m_player->setKeyPressed(value);



    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    decLives();
    return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
}

Actor* StudentWorld::createActor(Level::MazeEntry ge, double startX, double startY)
{
	int imageID = -1;
	Actor* result = nullptr;
	switch (ge)
	{
	case Level::player:
		result = new Penelope(startX, startY);
		break;
	case Level::smart_zombie:
		//result = new smartZombie(startX, startY);
		break;
	case Level::dumb_zombie:
		//result = new dumbZombie(startX, startY);
		break;
	case Level::citizen:
		//result = new Citizen(startX, startY);
		break;
	case Level::wall:
		result = new Wall(startX, startY);
		break;
	case Level::exit:
		//result = new Exit(startX, startY);
		break;
	case Level::pit:
		//result = new Pit(startX, startY);
		break;
	case Level::vaccine_goodie:
		//result = new Vaccine(startX, startY);
		break;
	case Level::gas_can_goodie:
		//result = new GasCan(startX, startY);
		break;
	case Level::landmine_goodie:
		//result = new LandmineBox(startX, startY);
		break;
	}

	return result;
}





