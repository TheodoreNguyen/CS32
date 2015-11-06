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
	Actor(int imageID, int startX, int startY, Direction dir, StudentWorld* wp, bool collide) :
		GraphObject(imageID, startX, startY, dir), m_world(wp), m_collideable(collide){}
	virtual ~Actor(){}
	virtual void doSomething() = 0;
	bool getCollide(){ return m_collideable; }
	StudentWorld* getWorld() const{
		return m_world;
	}
	
private:
	StudentWorld* m_world;
	bool m_collideable;
};

class Exit : public Actor
{
public:
	Exit(int startX, int startY, StudentWorld* wp) :
		Actor(IID_EXIT, startX, startY, none, wp, true){setVisible(false);}
	virtual ~Exit(){}
	virtual void doSomething();
};

class Pickup : public Actor
{
public:
	Pickup(int imageID, int startX, int startY, StudentWorld* wp) :
		Actor(imageID, startX, startY, none, wp, true){}
	virtual ~Pickup(){}
private:

};

class Jewel : public Pickup
{
public:
	Jewel(int startX, int startY, StudentWorld* wp) :
		Pickup(IID_JEWEL, startX, startY, wp){
		setVisible(true);
	}
	virtual ~Jewel(){setVisible(false); }
	virtual void doSomething();

};

class Agent : public Actor
{ 
public:
	Agent(int imageID, int startX, int startY, Direction dir, StudentWorld* wp) :
		Actor(imageID, startX, startY, dir, wp, false), m_alive(true){}
	virtual ~Agent(){}
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
		Agent(IID_PLAYER, startX, startY, GraphObject::right, wp), m_hp(20), m_bullets(20), m_bonus(1000), m_finished(false),
		m_jewelsLeft(0){
		setVisible(true);
	}
	virtual ~Player(){ setVisible(false); }			//i recently modified constructor/destructor to setvisible
	virtual void doSomething();
	int getHpPercentage();
	int getAmmo(){ return m_bullets;}
	void reduceBonus();
	int getBonus(){ return m_bonus; }
	bool levelFinished(){ return m_finished; }
	void setToFinish(){ m_finished = true; }
	int jewelsLeft(){ return m_jewelsLeft; }
	void obtainJewel(){ m_jewelsLeft--; }
	void initializeJewel(){ m_jewelsLeft++; }
	void setJewels(int numjewels){ m_jewelsLeft = numjewels; }
private:
	int m_hp;
	int m_bullets;
	int m_bonus;
	bool m_finished;
	int m_jewelsLeft;
	
};

class Wall : public Actor
{
public:
	Wall(int startX, int startY, StudentWorld* wp) :
		Actor(IID_WALL, startX, startY, GraphObject::none, wp, false){
		setVisible(true);
	}
	virtual ~Wall(){ setVisible(false); };
	virtual void doSomething(){}
};



#endif // ACTOR_H_
