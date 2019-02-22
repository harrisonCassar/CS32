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

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
	m_player = nullptr;
	m_numCitizensLeft = 0;
	m_activeActors = 0;
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
	m_activeActors = 0;
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
				Level::MazeEntry ge = lev.getContentsOf(x, y);
				if (ge == Level::citizen)
					m_numCitizensLeft++;

				if (ge == Level::player)
					m_player = new Penelope(SPRITE_WIDTH * x, SPRITE_HEIGHT * y, this);
				else if (ge != Level::empty)
				{
					if (createActor(ge,x,y) == nullptr)
						return GWSTATUS_LEVEL_ERROR;
				}
			}
		}

		activateAllActors();
	}
	else
		return GWSTATUS_LEVEL_ERROR;

    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	list<Actor*>::iterator it = m_actorList.begin();

	m_player->doSomething();
	if (m_player->isDead())
	{
		decLives();
		return GWSTATUS_PLAYER_DIED;
	}

	while (it != m_actorList.end())
	{
		if ((*it)->isActive())
			(*it)->doSomething();

		if (m_player->isDead())
		{
			decLives();
			return GWSTATUS_PLAYER_DIED;
		}
			
		if (m_finishedLevel)
			return GWSTATUS_FINISHED_LEVEL;
		
		it++;
	}

	bool didNotDeleteSomething = false;
	while (!didNotDeleteSomething)
	{
		didNotDeleteSomething = true;
		for (list<Actor*>::iterator i = m_actorList.begin(); i != m_actorList.end(); i++)
		{
			if ((*i)->isDead())
			{
				cerr << "Deleting object!" << endl;

				delete (*i);
				m_actorList.erase(i);
				didNotDeleteSomething = false;
				m_activeActors--;
				cerr << "Success!" << endl;
				
				break;
			}
		}
	}
	activateAllActors();

	//update statistics line
	setGameStatText(updateStatLine());

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

int StudentWorld::decNumCitizensLeft()
{
	cerr << "--NumCitizensLeft: " << m_numCitizensLeft - 1 << endl;
	return --m_numCitizensLeft;
}

Actor* StudentWorld::getPlayer()
{
	return m_player;
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

	//check for boundary with Penelope
	if (src != m_player)
	{
		double p_x_min = m_player->getX();
		double p_y_min = m_player->getY();
		double p_x_max = p_x_min + SPRITE_WIDTH - 1;
		double p_y_max = p_y_min + SPRITE_HEIGHT - 1;

		if ((x_1 >= p_x_min && x_1 <= p_x_max) && (y_1 >= p_y_min && y_1 <= p_y_max))
			return true;
		if ((x_2 >= p_x_min && x_2 <= p_x_max) && (y_2 >= p_y_min && y_2 <= p_y_max))
			return true;
		if ((x_3 >= p_x_min && x_3 <= p_x_max) && (y_3 >= p_y_min && y_3 <= p_y_max))
			return true;
		if ((x_4 >= p_x_min && x_4 <= p_x_max) && (y_4 >= p_y_min && y_4 <= p_y_max))
			return true;
	}

	//check for boundary with all other actors (active, in list)
	while (it != m_actorList.end())
	{
		if (*it != src)
		{
			if ((*it)->blocksMovement())
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

bool StudentWorld::checkFireBoundaryAt(double dest_x, double dest_y)
{
	double x_1 = dest_x;
	double y_1 = dest_y;
	double x_2 = dest_x + SPRITE_WIDTH - 1;
	double y_2 = dest_y;

	double x_3 = dest_x + SPRITE_WIDTH - 1;
	double y_3 = dest_y + SPRITE_HEIGHT - 1;
	double x_4 = dest_x;
	double y_4 = dest_y + SPRITE_HEIGHT - 1;

	list<Actor*>::iterator it = m_actorList.begin();

	while (it != m_actorList.end())
	{
		if ((*it)->blocksFire())
		{
			double other_x_min = (*it)->getX();
			double other_y_min = (*it)->getY();
			double other_x_max = other_x_min + SPRITE_WIDTH - 1;
			double other_y_max = other_y_min + SPRITE_HEIGHT - 1;

			if ((x_1 >= other_x_min && x_1 <= other_x_max) && (y_1 >= other_y_min && y_1 <= other_y_max))
				return true;
			if ((x_2 >= other_x_min && x_2 <= other_x_max) && (y_2 >= other_y_min && y_2 <= other_y_max))
				return true;
			if ((x_3 >= other_x_min && x_3 <= other_x_max) && (y_3 >= other_y_min && y_3 <= other_y_max))
				return true;
			if ((x_4 >= other_x_min && x_4 <= other_x_max) && (y_4 >= other_y_min && y_4 <= other_y_max))
				return true;
		}

		it++;
	}

	return false;
}

bool StudentWorld::findNearestPlayer(double dest_x, double dest_y, double &distance, Actor* &nearest)
{
	nearest = nullptr;

	/*
	double p_x = m_player->getX();
	double p_y = m_player->getY();

	double x_difference = p_x - dest_x;
	double y_difference = p_y - dest_y;
	*/

	distance = calculateDistance(dest_x, dest_y, m_player->getX(), m_player->getY());

	nearest = m_player;
	return true;
}

bool StudentWorld::findNearestFriendly(double dest_x, double dest_y, double &distance, Actor* &nearest)
{
	list<Actor*>::iterator it = m_actorList.begin();

	nearest = nullptr;
	distance = -1;
	double candidateDistance = -1;

	if (m_numCitizensLeft == 0)
		return false;

	while (it != m_actorList.end())
	{
		if ((*it)->isFriendly())
		{
			candidateDistance = calculateDistance(dest_x, dest_y, (*it)->getX(), (*it)->getY());

			if (distance == -1)
			{
				distance = candidateDistance;
				nearest = *it;
			}
			else if (candidateDistance < distance)
			{
				distance = candidateDistance;
				nearest = *it;
			}
		}

		it++;
	}

	if (it == m_actorList.begin())
		return false;

	return true;
}

bool StudentWorld::findNearestEvil(double dest_x, double dest_y, double &distance, Actor* &nearest)
{
	list<Actor*>::iterator it = m_actorList.begin();

	nearest = nullptr;
	distance = -1;
	double candidateDistance = -1;

	while (it != m_actorList.end())
	{
		if ((*it)->isEvil())
		{
			candidateDistance = calculateDistance(dest_x, dest_y, (*it)->getX(), (*it)->getY());

			if (distance == -1)
			{
				distance = candidateDistance;
				nearest = *it;
			}
			else if (candidateDistance < distance)
			{
				distance = candidateDistance;
				nearest = *it;
			}
		}

		it++;
	}

	if (it == m_actorList.begin())
		return false;

	return true;
}

/*
bool StudentWorld::findNearest(double dest_x, double dest_y, std::string type, double &distance, Actor* &nearest)
{
	nearest = nullptr;

	if (type == "Penelope")
	{
		double p_x = m_player->getX();
		double p_y = m_player->getY();

		double x_difference = p_x - dest_x;
		double y_difference = p_y - dest_y;

		distance = (x_difference*x_difference) + (y_difference*y_difference);

		nearest = m_player;
		return true;
	}

	list<Actor*>::iterator it = m_actorList.begin();

	distance = -1;
	double candidateDistance = -1;

	if (type == "Citizen" && m_numCitizensLeft == 0)
		return false;

	while (it != m_actorList.end())
	{
		string actorType = (*it)->getType();
		if (actorType == "SmartZombie" || actorType == "DumbZombie")
			actorType = "Zombie";
		if (actorType == type)
		{
			double other_x = (*it)->getX();
			double other_y = (*it)->getY();

			double x_difference = other_x - dest_x;
			double y_difference = other_y - dest_y;

			double candidateDistance = (x_difference*x_difference) + (y_difference*y_difference);

			if (distance == -1)
			{
				distance = candidateDistance;
				nearest = *it;
			}
			else if (candidateDistance < distance)
			{
				distance = candidateDistance;
				nearest = *it;
			}
		}

		it++;
	}

	if (it == m_actorList.begin())
		return false;

	return true;
}*/

/*bool StudentWorld::checkOverlapWith(double curr_x, double curr_y, std::string type, Actor* &overlapped)
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
		string actorType = (*it)->getType();
		if (actorType == "SmartZombie" || actorType == "DumbZombie")
			actorType = "Zombie";
		if (actorType == type)
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
}*/

Actor* StudentWorld::createActor(Level::MazeEntry ge, double x, double y)
{
	Actor* result = nullptr;
	switch (ge)
	{
	case Level::player:
		result = new Penelope(SPRITE_WIDTH * x, SPRITE_HEIGHT * y,this);
		break;
	case Level::smart_zombie:
		result = new SmartZombie(SPRITE_WIDTH * x, SPRITE_HEIGHT * y, this);
		break;
	case Level::dumb_zombie:
		result = new DumbZombie(SPRITE_WIDTH * x, SPRITE_HEIGHT * y, this);
		break;
	case Level::citizen:
		result = new Citizen(SPRITE_WIDTH * x, SPRITE_HEIGHT * y, this);
		break;
	case Level::wall:
		result = new Wall(SPRITE_WIDTH * x, SPRITE_HEIGHT * y, this);
		break;
	case Level::exit:
		result = new Exit(SPRITE_WIDTH * x, SPRITE_HEIGHT * y, this);
		break;
	case Level::pit:
		result = new Pit(SPRITE_WIDTH * x, SPRITE_HEIGHT * y, this);
		break;
	case Level::vaccine_goodie:
		result = new VaccineGoodie(SPRITE_WIDTH * x, SPRITE_HEIGHT * y, this);
		break;
	case Level::gas_can_goodie:
		result = new GasCanGoodie(SPRITE_WIDTH * x, SPRITE_HEIGHT * y, this);
		break;
	case Level::landmine_goodie:
		result = new LandmineGoodie(SPRITE_WIDTH * x, SPRITE_HEIGHT * y, this);
		break;
	}
	
	if (result != nullptr)
		m_actorList.push_back(result);

	m_activeActors++;
	return result;
}

void StudentWorld::addActor(Actor* created)
{
	m_actorList.push_back(created);
	m_activeActors++;
}

/*Actor* StudentWorld::createActor(string type, double x, double y, int direction)
{
	Actor* result = nullptr;
	Level::MazeEntry ge;
	if (type == "Landmine")
	{
		result = new Landmine(x,y, this);
		m_actorList.push_back(result);
		m_activeActors++;
		return result;
	}
	else if (type == "Flame")
	{
		result = new Flame(x,y, direction, this);
		m_actorList.push_back(result);
		m_activeActors++;
		return result;
	}

	else if (type == "Vomit")
	{
		result = new Vomit(x,y, direction, this);
		m_actorList.push_back(result);
		m_activeActors++;
		return result;
	}

	if (type == "Penelope")
		ge = Level::player;
	else if (type == "SmartZombie")
		ge = Level::smart_zombie;
	else if (type == "DumbZombie")
		ge = Level::dumb_zombie;
	else if (type == "Citizen")
		ge = Level::citizen;
	else if (type == "Wall")
		ge = Level::wall;
	else if (type == "Exit")
		ge = Level::exit;
	else if (type == "Pit")
		ge = Level::pit;
	else if (type == "VaccineGoodie")
		ge = Level::vaccine_goodie;
	else if (type == "GasCanGoodie")
		ge = Level::gas_can_goodie;
	else if (type == "LandmineGoodie")
		ge = Level::landmine_goodie;
	
	return createActor(ge,x/SPRITE_WIDTH,y/SPRITE_HEIGHT);
}*/

void StudentWorld::infectAllOverlapping(Actor* src)
{
	list<Actor*>::iterator it = m_actorList.begin();

	if (checkOverlapWithInfectable(src, m_player))
	{
		cerr << "Infecting Penelope!" << endl;
		m_player->setInfected(true);
	}

	while (it != m_actorList.end())
	{
		if (checkOverlapWithInfectable(src, *it))
		{
			if (!((*it)->isInfected()))
			{
				(*it)->setInfected(true);
				playSound(SOUND_CITIZEN_INFECTED);
			}
		}

		it++;
	}
}

/*bool StudentWorld::checkSpecificOverlapWith(double curr_x, double curr_y, Actor* overlapped)
{
	double x_center = curr_x + SPRITE_WIDTH / 2;
	double y_center = curr_y + SPRITE_HEIGHT / 2;

	double other_x_center = overlapped->getX() + SPRITE_WIDTH / 2;
	double other_y_center = overlapped->getY() + SPRITE_HEIGHT / 2;

	double x_difference = other_x_center - x_center;
	double y_difference = other_y_center - y_center;

	double distance = (x_difference*x_difference) + (y_difference*y_difference);

	if (distance <= 100.0)
		return true;

	return false;
}*/

//might have to make sure to check for self object
void StudentWorld::damageAllOverlapping(Actor* src)
{
	list<Actor*>::iterator it = m_actorList.begin();

	if (checkOverlapWithDamageable(src,m_player))
	{
		cerr << "Damaging Penelope!" << endl;
		m_player->setDead();
	}

	while (it != m_actorList.end())
	{
		if (checkOverlapWithDamageable(src,*it))
		{
			(*it)->killByHazard();
		}

		it++;
	}
}

bool StudentWorld::checkOverlapWithDamageable(Actor* src, Actor* other)
{
	if (other->isDamageable())
	{
		return checkOverlap(src, other);
	}

	return false;
}

bool StudentWorld::checkOverlapWithCanPickup(Actor* src)
{
	list<Actor*>::iterator it = m_actorList.begin();

	if (m_player->canPickUp() && checkOverlap(src, m_player))
		return true;

	while (it != m_actorList.end())
	{
		if ((*it)->canPickUp() && (*it) != src && checkOverlap(src, *it))
			return true;

		it++;
	}

	return false;
}

bool StudentWorld::checkOverlapWithSavable(Actor* src, Actor* &overlapped)
{
	overlapped = nullptr;

	list<Actor*>::iterator it = m_actorList.begin();

	while (it != m_actorList.end())
	{
		if ((*it)->isSavable() && (*it) != src && checkOverlap(src, *it))
		{
			overlapped = *it;
			return true;
		}

		it++;
	}

	return false;
}

bool StudentWorld::checkOverlapWithCanActivateTraps(Actor* src)
{
	list<Actor*>::iterator it = m_actorList.begin();

	if (m_player->canActivateTraps() && checkOverlap(src, m_player))
	{
		return true;
	}

	while (it != m_actorList.end())
	{
		if ((*it)->canActivateTraps() && (*it) != src && checkOverlap(src, *it))
			return true;

		it++;
	}

	return false;
}

bool StudentWorld::checkOverlapWithInfectable(double x_pos, double y_pos)
{
	list<Actor*>::iterator it = m_actorList.begin();

	if (m_player->isInfectable() && checkOverlap(x_pos, y_pos, m_player))
	{
		return true;
	}

	while (it != m_actorList.end())
	{
		if ((*it)->isInfectable() && checkOverlap(x_pos, y_pos, *it))
			return true;

		it++;
	}

	return false;
}

bool StudentWorld::checkOverlapWithInfectable(Actor* src, Actor* other)
{
	if (other->isInfectable())
	{
		return checkOverlap(src, other);
	}

	return false;
}

bool StudentWorld::checkOverlapWithBlocksFire(double x_pos, double y_pos)
{
	list<Actor*>::iterator it = m_actorList.begin();

	while (it != m_actorList.end())
	{
		if ((*it)->blocksFire() && checkOverlap(x_pos, y_pos, *it))
			return true;

		it++;
	}

	return false;
}

bool StudentWorld::checkOverlap(Actor* src, Actor* other)
{
	double distance = calculateDistance(src->getX(), src->getY(), other->getX(), other->getY());

	if (distance <= 100.0)
		return true;
	else
		return false;
}

bool StudentWorld::checkOverlap(double x_pos, double y_pos, Actor* other)
{
	double distance = calculateDistance(x_pos, y_pos, other->getX(), other->getY());

	if (distance <= 100.0)
		return true;
	else
		return false;
}

double StudentWorld::calculateDistance(double x_src, double y_src, double x_other, double y_other)
{
	double x_center = x_src + SPRITE_WIDTH / 2;
	double y_center = y_src + SPRITE_HEIGHT / 2;

	double other_x_center = x_other + SPRITE_WIDTH / 2;
	double other_y_center = y_other + SPRITE_HEIGHT / 2;

	double x_difference = other_x_center - x_center;
	double y_difference = other_y_center - y_center;

	return (x_difference*x_difference) + (y_difference*y_difference);

}

void StudentWorld::activateAllActors()
{
	list<Actor*>::iterator it = m_actorList.begin();

	while (it != m_actorList.end())
	{
		(*it)->setActive(true);

		it++;
	}
}

string StudentWorld::updateStatLine()
{
	//declare stringstream
	ostringstream oss;
	oss.setf(ios::fixed);
	oss.precision(2);

	//get updated statistics
	int score = getScore();
	int level = getLevel();
	int lives = getLives();
	int sVaccines = m_player->getSupplyVaccines();
	int sFlames = m_player->getSupplyFlamethrower();
	int sLandmines = m_player->getSupplyLandmines();
	int infectedCount = m_player->getInfectedCount();

	//properly add score value
	int magnitude = 0;
	int scoreCopy;
	if (score < 0)
		scoreCopy = score * -1;
	else
		scoreCopy = score;

	for (; ;)
	{
		scoreCopy /= 10;
		magnitude++;

		if (scoreCopy == 0)
			break;
	}
	
	oss << "Score: ";
	
	if (score < 0)
	{
		oss << "-";
		score *= -1;
		magnitude++;
	}

	for (int i = 0; i < 6 - magnitude; i++)
		oss << "0";

	oss << score << "  ";

	//add the rest with proper formatting
	oss << "Level: " << level << "  ";
	oss << "Lives: " << lives << "  ";
	oss << "Vaccines: " << sVaccines << "  ";
	oss << "Flames: " << sFlames << "  ";
	oss << "Mines: " << sLandmines << "  ";
	oss << "Infected: " << infectedCount;

	return oss.str();
}

void StudentWorld::updateFlamethrowerSupply(int value)
{
	m_player->incSupplyFlamethrower(value);
}

void StudentWorld::updateLandmineSupply(int value)
{
	m_player->incSupplyLandmines(value);
}

void StudentWorld::updateVaccineSupply(int value)
{
	m_player->incSupplyVaccines(value);
}