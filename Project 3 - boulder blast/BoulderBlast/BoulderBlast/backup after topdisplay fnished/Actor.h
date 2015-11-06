#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
using namespace std;

#include "StudentWorld.h"
class Actor : public GraphObject
{
public:
	Actor(int imageID, int startX, int startY, Direction dir, StudentWorld* wp) :
		GraphObject(imageID, startX, startY, dir), m_world(wp){}
	virtual ~Actor(){}
	virtual void doSomething() = 0;
	StudentWorld* getWorld() const{
		return m_world;
	}
	
private:
	StudentWorld* m_world;
};

class Agent : public Actor
{ 
public:
	Agent(int imageID, int startX, int startY, Direction dir, StudentWorld* wp) :
		Actor(imageID, startX, startY, dir, wp), m_alive(true){}
	bool alive(){ return m_alive; }
	void setAlive(){ m_alive = true; }
	void setDead(){ m_alive = false; }
private:
	bool m_alive;
};

class Player : public Agent
{
public: 
	Player(int startX, int startY, StudentWorld* wp) :
		Agent(IID_PLAYER, startX, startY, GraphObject::right, wp), m_hp(20), m_bullets(20), m_bonus(1000){
		setVisible(true);
	}
	virtual ~Player(){ setVisible(false); }			//i recently modified constructor/destructor to setvisible
	virtual void doSomething();
	int getHpPercentage();
	int getAmmo(){ return m_bullets;}
	void reduceBonus();
	int getBonus(){ return m_bonus; }
private:
	int m_hp;
	int m_bullets;
	int m_bonus;
};

class Wall : public Actor
{
public:
	Wall(int startX, int startY, StudentWorld* wp):
		Actor(IID_WALL, startX, startY, GraphObject::none, wp){
		setVisible(true);
	}
	virtual ~Wall(){ setVisible(false); };
	virtual void doSomething(){}
};



#endif // ACTOR_H_
