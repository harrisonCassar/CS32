#include "StudentWorld.h"
#include "GameConstants.h"
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
	Level lev(assetPath());
	string levelFile = "level01.txt";
	Level::LoadResult result = lev.loadLevel(levelFile);
	if (result == Level::load_fail_file_not_found)
		cerr << "Cannot find level01.txt data file" << endl;
	else if (result == Level::load_fail_bad_format)
		cerr << "Your level was improperly formatted" << endl;
	else if (result == Level::load_success)
	{
		cerr << "Successfully loaded level" << endl;

		for (int y = 0; y < VIEW_HEIGHT / SPRITE_HEIGHT; y++)
		{
			for (int x = 0; x < VIEW_WIDTH / SPRITE_WIDTH; x++)
			{
				Level::MazeEntry ge = lev.getContentsOf(x, y);
				if (ge != Level::empty)
				{

				}
				Actor* temp = createActor(ge);
				m_actorList.push_back(temp);
			}
		}

	}
	else
		return GWSTATUS_LEVEL_ERROR;

    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    decLives();
    return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
}

Actor* StudentWorld::createActor(Level::MazeEntry ge)
{
	int imageID = -1;
	switch (ge)
	{
		case Level::player:
			imageID = IID_PLAYER;
			break;
		case Level::smart_zombie:
		case Level::dumb_zombie:
			imageID = IID_ZOMBIE;
			break;
		case Level::citizen:
			imageID = IID_CITIZEN;
			break;
		

			/*...... LEFT OFF HERE SDFIJIJDIJDSIJD..... sdadfjklasdfsdhjfoasdjkfjaslkdklfjaslfj;kdasjfjasdkljfjasdkl;fk;jasjklfkasjklkdfsalfasfjk*/

		}

	const int IID_FLAME = 3;
	const int IID_VOMIT = 4;
	const int IID_PIT = 5;
	const int IID_LANDMINE = 6;
	const int IID_VACCINE_GOODIE = 7;
	const int IID_GAS_CAN_GOODIE = 8;
	const int IID_LANDMINE_GOODIE = 9;
	const int IID_EXIT = 10;
	const int IID_WALL = 11;



	}
}
}




