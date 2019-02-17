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
	m_player = nullptr;
	m_numCitizensLeft = 0;
	m_finishedLevel = false;
}

StudentWorld::~StudentWorld()
{
	cleanUp();
}

int StudentWorld::init()
{
	//reset certain member variables
	m_numCitizensLeft = 0;
	m_player = nullptr;
	m_finishedLevel = false;

	//construct new level object
	Level lev(assetPath());

	//construct path for current level
	ostringstream oss;
	oss.setf(ios::fixed);
	oss.precision(2);

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
				cerr << x << " " << y << endl;
				
				Level::MazeEntry ge = lev.getContentsOf(x, y);
				if (ge == Level::citizen)
					m_numCitizensLeft++;

				if (ge == Level::player)
					m_player = new Penelope(SPRITE_WIDTH * x, SPRITE_HEIGHT * y, this);
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
	list<Actor*>::iterator it = m_actorList.begin();

	m_player->doSomething();

	while (it != m_actorList.end())
	{
		(*it)->doSomething();
		it++;
	}
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //decLives();

	if (m_finishedLevel)
		return GWSTATUS_FINISHED_LEVEL;

    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
	list<Actor*>::iterator it = m_actorList.begin();

	while (it != m_actorList.end())
	{
		delete (*it);
		it = m_actorList.erase(it);
	}

	if (m_player != nullptr)
		delete m_player;
}

void StudentWorld::finishLevel()
{
	m_finishedLevel = true;
}

int StudentWorld::getNumCitizensLeft()
{
	return m_numCitizensLeft;
}

bool StudentWorld::checkBoundaryAt(double dest_x, double dest_y, Actor* src)
{
	double x_1 = dest_x;
	double y_1 = dest_y;
	double x_2 = dest_x + SPRITE_WIDTH-1;
	double y_2 = dest_y;

	double x_3 = dest_x + SPRITE_WIDTH-1;
	double y_3 = dest_y + SPRITE_HEIGHT-1;
	double x_4 = dest_x;
	double y_4 = dest_y + SPRITE_HEIGHT-1;

	list<Actor*>::iterator it = m_actorList.begin();

	while (it != m_actorList.end())
	{
		std::string type = (*it)->getType();

		if (*it != src)
		{
			if (type == "Zombie" || type == "Penelope" || type == "Citizen" || type == "Wall")
			{
				double other_x_min = (*it)->getX();
				double other_y_min = (*it)->getY();
				double other_x_max = other_x_min + SPRITE_WIDTH-1;
				double other_y_max = other_y_min + SPRITE_HEIGHT-1;

				if ((x_1 >= other_x_min && x_1 <= other_x_max) && (y_1 >= other_y_min && y_1 <= other_y_max))
					return true;
				if ((x_2 >= other_x_min && x_2 <= other_x_max) && (y_2 >= other_y_min && y_2 <= other_y_max))
					return true;
				if ((x_3 >= other_x_min && x_3 <= other_x_max) && (y_3 >= other_y_min && y_3 <= other_y_max))
					return true;
				if ((x_4 >= other_x_min && x_4 <= other_x_max) && (y_4 >= other_y_min && y_4 <= other_y_max))
					return true;
			}
		}

		it++;
	}

	return false;
}

bool StudentWorld::checkOverlapWith(double curr_x, double curr_y, std::string type, Actor* overlapped)
{
	if (type == "Penelope")
	{
		double x_center = curr_x + SPRITE_WIDTH / 2.0;
		double y_center = curr_y + SPRITE_HEIGHT / 2.0;

		double other_x_center = m_player->getX() + SPRITE_WIDTH / 2.0;
		double other_y_center = m_player->getY() + SPRITE_HEIGHT / 2.0;

		double x_difference = other_x_center - x_center;
		double y_difference = other_y_center - y_center;

		double distance = (x_difference*x_difference) + (y_difference*y_difference);

		if (distance <= 100.0)
		{
			overlapped = m_player;
			return true;
		}
	}

	list<Actor*>::iterator it = m_actorList.begin();

	while (it != m_actorList.end())
	{
		if ((*it)->getType() == type)
		{
			double x_center = curr_x + SPRITE_WIDTH/2;
			double y_center = curr_y + SPRITE_HEIGHT/2;

			double other_x_center = (*it)->getX() + SPRITE_WIDTH / 2;
			double other_y_center = (*it)->getY() + SPRITE_HEIGHT / 2;

			double x_difference = other_x_center - x_center;
			double y_difference = other_y_center - y_center;

			double distance = (x_difference*x_difference) + (y_difference*y_difference);

			if (distance <= 100.0)
			{
				overlapped = (*it);
				return true;
			}
		}

		it++;
	}
	
	return false;
}

Actor* StudentWorld::createActor(Level::MazeEntry ge, double x, double y)
{
	int imageID = -1;
	Actor* result = nullptr;
	switch (ge)
	{
	case Level::player:
		result = new Penelope(SPRITE_WIDTH * x, SPRITE_HEIGHT * y,this);
		break;
	case Level::smart_zombie:
		//result = new smartZombie(SPRITE_WIDTH * x, SPRITE_HEIGHT * y, this);
		break;
	case Level::dumb_zombie:
		//result = new dumbZombieSPRITE_WIDTH * x, SPRITE_HEIGHT * y, this);
		break;
	case Level::citizen:
		//result = new Citizen(SPRITE_WIDTH * x, SPRITE_HEIGHT * y, this);
		result = new Wall(SPRITE_WIDTH * x, SPRITE_HEIGHT * y, this);
		break;
	case Level::wall:
		result = new Wall(SPRITE_WIDTH * x, SPRITE_HEIGHT * y, this);
		break;
	case Level::exit:
		result = new Exit(SPRITE_WIDTH * x, SPRITE_HEIGHT * y, this);
		break;
	case Level::pit:
		//result = new Pit(SPRITE_WIDTH * x, SPRITE_HEIGHT * y, this);
		break;
	case Level::vaccine_goodie:
		//result = new Vaccine(SPRITE_WIDTH * x, SPRITE_HEIGHT * y, this);
		break;
	case Level::gas_can_goodie:
		//result = new GasCan(SPRITE_WIDTH * x, SPRITE_HEIGHT * y, this);
		break;
	case Level::landmine_goodie:
		//result = new LandmineBox(SPRITE_WIDTH * x, SPRITE_HEIGHT * y, this);
		break;
	}

	return result;
}





