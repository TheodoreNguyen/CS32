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
		GraphObject(imageID, startX, startY, dir), m_world(wp), m_collideable(collide), m_actorType(imageID){}
	virtual ~Actor(){}
	virtual void doSomething() = 0;
	bool getCollide(){ return m_collideable; }
	int getActorType(){ return m_actorType; }
	StudentWorld* getWorld() const{
		return m_world;
	}
	
private:
	StudentWorld* m_world;
	bool m_collideable;
	int m_actorType;
};

class Bullet : public Actor
{
public:
	Bullet(int startX, int startY, StudentWorld* wp, Direction dir) :
		Actor(IID_BULLET, startX, startY, dir, wp, true){
		setVisible(true);
	}
	virtual ~Bullet(){ setVisible(false); }
	virtual void doSomething(){}
};

class Hole : public Actor
{
public:
	Hole(int startX, int startY, StudentWorld* wp) :
		Actor(IID_HOLE, startX, startY, none, wp, false){
		setVisible(true);
	}
	virtual ~Hole(){ setVisible(false); }
	virtual void doSomething(){}
};

class Boulder : public Actor
{
public:
	Boulder(int startX, int startY, StudentWorld* wp) :
	Actor(IID_BOULDER, startX, startY, none, wp, false), m_hp(10){
		setVisible(true);
	}
	virtual ~Boulder(){ setVisible(false); }
	virtual void doSomething(){}
	void damageBoulder(){ m_hp = m_hp - 2; }
private:
	int m_hp;

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

class Goodie : public Pickup
{
public:
	Goodie(int imageID, int startX, int startY, StudentWorld* wp) :
		Pickup(imageID, startX, startY, wp){}
	virtual ~Goodie(){}

};

class AmmoGoodie : public Goodie
{
public:
	AmmoGoodie(int startX, int startY, StudentWorld* wp) :
		Goodie(IID_AMMO, startX, startY, wp){
		setVisible(true);
	}
	virtual ~AmmoGoodie(){ setVisible(false); }
	virtual void doSomething();
};

class RestoreHealthGoodie : public Goodie
{
public:
	RestoreHealthGoodie(int startX, int startY, StudentWorld* wp) :
		Goodie(IID_RESTORE_HEALTH, startX, startY, wp){
		setVisible(true);
	}
	virtual ~RestoreHealthGoodie(){ setVisible(false); }
	virtual void doSomething();

};

class ExtraLifeGoodie : public Goodie
{
public:
	ExtraLifeGoodie(int startX, int startY, StudentWorld* wp) :
		Goodie(IID_EXTRA_LIFE, startX, startY, wp){
		setVisible(true);
	}
	virtual ~ExtraLifeGoodie(){ setVisible(false); }
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
	void damagePlayer(){
		m_hp = m_hp - 2;
	}
	void increaseHp(){ m_hp = 20; }
	void increaseammo(){ m_bullets = m_bullets + 20; }
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
