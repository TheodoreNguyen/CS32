#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include "Level.h"
#include <vector>
#include <sstream>

using namespace std;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class Actor;
class Player;
class StudentWorld : public GameWorld

{
public:
	StudentWorld(std::string assetDir) :
		GameWorld(assetDir), m_level(0), m_player(NULL){}

	~StudentWorld();

	//int Levelfcn(int lvl);

	virtual int init();
	/*{
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
		StudentWorld::m_actors.push_back(new Player(x, y, this));
		break;
		case Level::wall:
		StudentWorld::m_actors.push_back(new Wall(x, y, this));
		break;
		default:
		break;
		}
		}
		}
		}

		return GWSTATUS_CONTINUE_GAME;
		}*/

	virtual int move();
	//{
	// This code is here merely to allow the game to build, run, and terminate after hitting enter a few times 
	//decLives();
	//return GWSTATUS_CONTINUE_GAME;
	//}
	int numActors() { return m_actors.size(); }
	bool canIMoveThere(int x, int y);

	virtual void cleanUp();
	void addActor(Actor* add){ m_actors.push_back(add); }
	int level() const { return m_level; }
	void increaselvl(){ m_level++; }
	Player* getPlayer(){ return m_player; }
	vector<Actor*> getActorArray(){ return m_actors; }
	string filename(int lvl)
	{
		Level lev(assetDirectory());
		ostringstream oss;
		if (m_level >= 0 && m_level <= 9)
			oss << "level0" << m_level << ".dat";
		else if (m_level >= 10 && m_level <= 99)
			oss << "level" << m_level << ".dat";
		else
			return "";
		return oss.str();
	}
	
	void updateDisplayText();
	bool gameFinished();
	bool AllJewelsCollected();
private:
	vector<Actor*> m_actors;
	Player* m_player;
	int m_level;
};

#endif // STUDENTWORLD_H_
