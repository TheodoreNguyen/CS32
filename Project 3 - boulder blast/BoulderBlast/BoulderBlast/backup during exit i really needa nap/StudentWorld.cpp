#include "StudentWorld.h"
#include <string>
using namespace std;
#include "Level.h"
#include <sstream>
#include <vector>
#include "GameConstants.h"
#include "Actor.h"
GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::~StudentWorld()
{
	cleanUp();
}

bool StudentWorld::canIMoveThere(int x, int y)
{
	for (int i = 0; i != numActors(); i++)
	{
		if (x == m_actors[i]->getX() && y == m_actors[i]->getY())
			return false;
	}
	return true;
}

void StudentWorld::updateDisplayText()
{
	int score = getScore();
	int level = getLevel();
	unsigned int bonus = m_player->getBonus();
	int livesLeft = getLives();

	int scoreSize = 0;
	if (score >= 0 && score <= 9)
		scoreSize = 1;
	else if (score >= 10 && score <= 99)
		scoreSize = 2;
	else if (score >= 100 && score <= 999)
		scoreSize = 3;
	else if (score >= 1000 && score <= 9999)
		scoreSize = 4;
	else if (score >= 10000 && score <= 99999)
		scoreSize = 5;
	else if (score >= 100000 && score <= 999999)
		scoreSize = 6;
	else if (score >= 1000000)
		scoreSize = 7;
	ostringstream ssscore;
	switch (scoreSize)
	{
	case 1:
		ssscore << "000000" << score;
		break;
	case 2:
		ssscore << "00000" << score;
		break;
	case 3:
		ssscore << "0000" << score;
		break;
	case 4:
		ssscore << "000" << score;
		break;
	case 5:
		ssscore << "00" << score;
		break;
	case 6:
		ssscore << "0" << score;
		break;
	case 7:
		if (score > 9999999)
			score = 9999999;
		ssscore << score;
		break;
	default: 

		break;
	}
	ostringstream sslevel;
	if (level >= 0 && level <= 9)
		sslevel << "0" << level;
	else if (level >= 10 && level <= 99)
		sslevel << level;
	else if (level > 99)
		return;

	ostringstream oss;
	oss << "Score: " << ssscore.str() << " Level: " << sslevel.str()
		<< " Lives: " << getLives() << " Health: " << m_player->getHpPercentage()
		<< "% Ammo: " << m_player->getAmmo() << " Bonus: " << m_player->getBonus();

	string s = oss.str();
	setGameStatText(s);

}




int StudentWorld::init()
{
	Level lev(assetDirectory());
	ostringstream oss;
	if (m_level >= 0 && m_level <= 9)
		oss << "level0" << m_level << ".dat";
	else if (m_level >= 10 && m_level <= 99)
		oss << "level" << m_level << ".dat";
	else
		return GWSTATUS_PLAYER_WON; //okay
	string levelname = oss.str();
	Level::LoadResult result = lev.loadLevel(levelname);
	if (result == Level::load_fail_file_not_found)
		return GWSTATUS_LEVEL_ERROR;						//cerr << "Could not find level00.dat data file\n";
	else if (result == Level::load_fail_bad_format)
		return GWSTATUS_LEVEL_ERROR;
	else if (result == Level::load_success)
	{
		for (int x = 0; x != VIEW_WIDTH; x++)
		{
			for (int y = 0; y != VIEW_HEIGHT; y++)
			{
				Level::MazeEntry ge = lev.getContentsOf(x, y);
				switch (ge)
				{
				case Level::player:
					m_player = new Player(x, y, this);
					m_player->GraphObject::setVisible(true);
					//StudentWorld::m_actors.push_back(m_player);
					break;
				case Level::wall:
					StudentWorld::m_actors.push_back(new Wall(x, y, this));
					m_actors[m_actors.size() - 1]->GraphObject::setVisible(true);
					break;
				default:
					break;
				}
			}
		}
	}

	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	updateDisplayText();

	m_player->doSomething();
	//vector<Actor*>::iterator p = m_actors.begin();		5 bucks thats the crash - thats the crash but idk why
	for (int i = 0; i != m_actors.size(); i++)
	{
		if (m_actors[i]->isVisible())
			m_actors[i]->doSomething();

		if (!(m_player->alive()))
		{
			GameWorld::playSound(SOUND_PLAYER_DIE);
			decLives();
			//delete m_player;						//does not crash uner this command
			return GWSTATUS_PLAYER_DIED;
		}
			//IF PLAYER FINISHED LEVEL
	}
	
	//remove dead actors after each tick
		//do this by checking if the actor is of type agent, then checking if it is dead or alive, then setting invisible

	m_player->reduceBonus();

	//if all jewels collected, expose exit

	if (!(m_player->alive()))
	{
		GameWorld::playSound(SOUND_PLAYER_DIE);
		decLives();
		//delete m_player;						//does not crash uner this command
		return GWSTATUS_PLAYER_DIED;
	}

	//IF PLAYER FINISHED LEVEL

	return GWSTATUS_CONTINUE_GAME;
}
											//i was trying to implement cleanup and the destructr
void StudentWorld::cleanUp()
{
	vector<Actor*>::iterator p = m_actors.begin();
	while (p != m_actors.end())
	{
		(*p)->GraphObject::setVisible(false);
		delete (*p);
		p = m_actors.erase(p);
	}
	m_player->GraphObject::setVisible(false);
	delete m_player;
}
/*
int StudentWorld::Levelfcn(int lvl)
{
	Level lev(assetDirectory());
	ostringstream oss;
	if (lvl >= 0 && lvl <= 9)
		oss << "level0" << lvl << ".dat";
	else if (lvl >= 10 && lvl <= 99)
		oss << "level" << lvl << ".dat";
	else
		return 14;	
	string levelname = oss.str();
	Level::LoadResult result = lev.loadLevel(levelname);
	if (result == Level::load_fail_file_not_found)
		return 15;						//cerr << "Could not find level00.dat data file\n";
	else if (result == Level::load_fail_bad_format)
		return 16;						// cerr << "Your level was improperly formatted\n";
	else if (result == Level::load_success)
	{
		for (int x = 0; x != VIEW_WIDTH; x++)
		{
			for (int y = 0; y != VIEW_HEIGHT; y++)
			{
				Level::MazeEntry ge = lev.getContentsOf(x, y);
				switch (ge)
				{
				case Level::player:
					StudentWorld::m_actors.push_back(new Actor(IID_PLAYER, x, y, GraphObject::right, this));
					break;
				case Level::wall:
					StudentWorld::m_actors.push_back(new Actor(IID_WALL, x, y, GraphObject::none, this));
					break;
				default:
					break;
				}
			}
		}
	}
	return 0;
}*/