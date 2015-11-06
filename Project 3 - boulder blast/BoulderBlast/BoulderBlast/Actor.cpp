#include "Actor.h"
#include "StudentWorld.h"
#include <vector>
#include "GraphObject.h"
#include <cstdlib>
// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

void KleptoBotFactory::doSomething()
{

}

void KleptoBot::doSomething()
{
	if (getHp() <= 0)
	{
		setDead();
		setVisible(false);
		getWorld()->playSound(SOUND_ROBOT_DIE);
		return;
	}
	ticks++;
	bool bulletshot = false;
	if (ticks % m_ticks == 0)
	{

		if (!bulletshot)
		{
			if (!(getWorld()->canIMoveThere(getX(), getY() + 1)))
				setDirection(down);
			else
				moveTo(getX(), getY() + 1);
		}

	}

}

void Hole::doSomething()
{
	if (isVisible())
	{
		Boulder* ptr;
		vector<Boulder*> listBoulders;
		for (int i = 0; i != getWorld()->getActorArray().size(); i++)
		{
			ptr = dynamic_cast<Boulder*>(getWorld()->getActorArray()[i]);
			if (ptr != nullptr)
				listBoulders.push_back(ptr);
		}
		for (int i = 0; i != listBoulders.size(); i++)
		{
			if (getY() == listBoulders[i]->getY() && getX() == listBoulders[i]->getX())
			{
				setVisible(false);
				listBoulders[i]->setVisible(false);

			}
		}
	}
}

void SnarlBot::doSomething()
{
	if (getHp() <= 0)
	{
		setDead();
		setVisible(false);
		getWorld()->playSound(SOUND_ROBOT_DIE);
		return;
	}
	ticks++;
	bool bulletshot;
	if (ticks % m_ticks == 0)
	{
		switch (getDirection())
		{
		case up:
			bulletshot = false;
			for (int i = 1; true; i++)
			{
			/*	if (!(getWorld()->canIMoveThere(getX(), getY() + i)))
				{
					break;
				}
				else if (getX() == getWorld()->getPlayer()->getX() && getY() + i == getWorld()->getPlayer()->getY())
				{
					getWorld()->pushBackBullet(getX(), getY() + 1, getWorld(), up);
					getWorld()->playSound(SOUND_ENEMY_FIRE);
					bulletshot = true;
					break;
				}*/
				if (getX() == getWorld()->getPlayer()->getX() && getWorld()->canIMoveThere(getY() + i, getX()))
				{
					getWorld()->pushBackBullet(getX(), getY() + 1, getWorld(), right);
					bulletshot = true;
					break;
				}
				if (!getWorld()->canIMoveThere(getY() + i, getX()))
					break;
			}
			if (!bulletshot)
			{
				if (!(getWorld()->canIMoveThere(getX(), getY() + 1)))
					setDirection(down);
				else
					moveTo(getX(), getY() + 1);
			}
			break;
		case right:
			bulletshot = false;
			for (int i = 1; true; i++)
			{/*
				if (!(getWorld()->canIMoveThere(getX() + i, getY())))
				{
					break;
				}
				else if (getX() + i == getWorld()->getPlayer()->getX() && getY() == getWorld()->getPlayer()->getY())
				{
					getWorld()->pushBackBullet(getX() + 1, getY(), getWorld(), right);
					bulletshot = true;
					break;
				}*/
				if (getY() == getWorld()->getPlayer()->getY() && getWorld()->canIMoveThere(getY(), getX() + i))
				{
					getWorld()->pushBackBullet(getX() + 1, getY(), getWorld(), right);
					bulletshot = true;
					break;
				}
				if (!getWorld()->canIMoveThere(getY(), getX() + i))
					break;
			}
			if (!bulletshot)
			{
				if (!(getWorld()->canIMoveThere(getX() + 1, getY())))
					setDirection(left);
				else
					moveTo(getX() + 1, getY());
			}
			break;
		case down:
			bulletshot = false;
			for (int i = 1; true; i++)
			{
				/*if (!(getWorld()->canIMoveThere(getX(), getY() - i)))
				{
					break;
				}
				else if (getX() == getWorld()->getPlayer()->getX() && getY() - i == getWorld()->getPlayer()->getY())
				{
					getWorld()->pushBackBullet(getX(), getY() - 1, getWorld(), down);
					bulletshot = true;
					break;
				}*/
				if (getX()== getWorld()->getPlayer()->getX() && getWorld()->canIMoveThere(getY() - i, getX()))
				{
					getWorld()->pushBackBullet(getX() , getY() - 1, getWorld(), right);
					bulletshot = true;
					break;
				}
				if (!getWorld()->canIMoveThere(getY() - i, getX() ))
					break;
			}
			if (!bulletshot)
			{
				if (!(getWorld()->canIMoveThere(getX(), getY() - 1)))
					setDirection(up);
				else
					moveTo(getX(), getY() - 1);
			}
			break;
		case left:
			bulletshot = false;
			for (int i = 1; true; i++)
			{
			/*	if (!(getWorld()->canIMoveThere(getX() - i, getY())))
				{
					break;
				}
				else if (getX() - i == getWorld()->getPlayer()->getX() && getY() == getWorld()->getPlayer()->getY())
				{
					getWorld()->pushBackBullet(getX() - 1, getY(), getWorld(), left);
					bulletshot = true;
					break;
				}*/
				if (getY() == getWorld()->getPlayer()->getY() && getWorld()->canIMoveThere(getY(), getX() - i))
				{
					getWorld()->pushBackBullet(getX() - 1, getY(), getWorld(), right);
					bulletshot = true;
					break;
				}
				if (!getWorld()->canIMoveThere(getY(), getX() - i))
					break;
			}
			if (!bulletshot)
			{
				if (!(getWorld()->canIMoveThere(getX() - 1, getY())))
					setDirection(right);
				else
					moveTo(getX() - 1, getY());
			}
			break;
		}
	}
	else
		return;

}

bool Boulder::moveBoulder(Direction dir)
{
	Hole* ptr;
	vector<Hole*> listHoles;
	for (int i = 0; i != getWorld()->getActorArray().size(); i++)
	{
		ptr = dynamic_cast<Hole*>(getWorld()->getActorArray()[i]);
		if (ptr != nullptr)
			listHoles.push_back(ptr);
	}
	
	switch (dir)
	{
	case up:
		if (getWorld()->canIMoveThere(getX(), getY() + 1))
		{
			moveTo(getX(), getY() + 1);
			return true;
		}
		for (int i = 0; i != listHoles.size(); i++)
		{
			if (getX() == listHoles[i]->getX() && getY() + 1 == listHoles[i]->getY())
			{
				moveTo(getX(), getY() + 1);
				return true;
			}
		}
		break;
	case down:
		if (getWorld()->canIMoveThere(getX(), getY() - 1))
		{
			moveTo(getX(), getY() - 1);
			return true;
		}
		for (int i = 0; i != listHoles.size(); i++)
		{
			if (getX() == listHoles[i]->getX() && getY() - 1 == listHoles[i]->getY())
			{
				moveTo(getX(), getY() - 1);
				return true;
			}
		}
		break;
	case right:
		if (getWorld()->canIMoveThere(getX() + 1, getY()))
		{
			moveTo(getX() + 1, getY());
			return true;
		}
		for (int i = 0; i != listHoles.size(); i++)
		{
			if (getX()+ 1 == listHoles[i]->getX() && getY() == listHoles[i]->getY())
			{
				moveTo(getX() + 1, getY());
				return true;
			}
		}
		break;
	case left:
		if (getWorld()->canIMoveThere(getX() - 1, getY()))
		{
			moveTo(getX() - 1, getY());
			return true;
		}
		for (int i = 0; i != listHoles.size(); i++)
		{
			if (getX() - 1 == listHoles[i]->getX() && getY() == listHoles[i]->getY())
			{
				moveTo(getX() - 1, getY());
				return true;
			}
		}
		break;
	}
	return false;
}

void Boulder::doSomething()
{
	if (m_hp <= 0) 
		setVisible(false);
}

void Bullet::doSomething()
{
	if (isVisible())
	{
		
		if (getX() == getWorld()->getPlayer()->getX() && getY() == getWorld()->getPlayer()->getY())
		{
			getWorld()->playSound(SOUND_PLAYER_IMPACT);
			getWorld()->getPlayer()->damagePlayer();
			setVisible(false);
			return;
		}
		for (int i = 0; i != getWorld()->getActorArray().size(); i++)
		{
			if (getX() == getWorld()->getActorArray()[i]->getX() && getY() == getWorld()->getActorArray()[i]->getY())
			{
				if (getWorld()->getActorArray()[i]->getActorType() == IID_WALL)
				{
					setVisible(false);
					return;
				}
				if (getWorld()->getActorArray()[i]->getActorType() == IID_BOULDER)
				{
					Boulder* ptr = dynamic_cast<Boulder*>(getWorld()->getActorArray()[i]);
					ptr->damageBoulder();
					setVisible(false);
					return;
				}
				else if (getWorld()->getActorArray()[i]->getActorType() == IID_SNARLBOT ||
					getWorld()->getActorArray()[i]->getActorType() == IID_KLEPTOBOT ||
					getWorld()->getActorArray()[i]->getActorType() == IID_ANGRY_KLEPTOBOT)
				{
					getWorld()->playSound(SOUND_ROBOT_IMPACT);
					Robot* ptr = dynamic_cast<Robot*>(getWorld()->getActorArray()[i]);
					ptr->damageRobot();
					setVisible(false);
					return;
				}
			}
			

		}
		
		switch (getDirection())
		{
		case up:
			moveTo(getX(), getY() + 1);
			break;
		case right:
			moveTo(getX() + 1, getY());
			break;
		case down:
			moveTo(getX(), getY() - 1);
			break;
		case left: 
			moveTo(getX() - 1, getY());
			break;
		default: 
			break;
		}
	}
	return;
}


void AmmoGoodie::doSomething()
{
	if (isVisible())
	{
		if (getWorld()->getPlayer()->getX() == getX() && getWorld()->getPlayer()->getY() == getY())
		{
			getWorld()->increaseScore(100);
			getWorld()->GameWorld::playSound(SOUND_GOT_GOODIE);
			getWorld()->getPlayer()->increaseammo();
			setVisible(false);
		}
	}
	return;
}

void RestoreHealthGoodie::doSomething()
{
	if (isVisible())
	{
		if (getWorld()->getPlayer()->getX() == getX() && getWorld()->getPlayer()->getY() == getY())
		{
			getWorld()->increaseScore(500);
			getWorld()->GameWorld::playSound(SOUND_GOT_GOODIE);
			getWorld()->getPlayer()->increaseammo();
			setVisible(false);
		}
	}
	return;
}

void ExtraLifeGoodie::doSomething()
{
	if (isVisible())
	{
		if (getWorld()->getPlayer()->getX() == getX() && getWorld()->getPlayer()->getY() == getY())
		{
			getWorld()->increaseScore(1000);
			getWorld()->GameWorld::playSound(SOUND_GOT_GOODIE);
			getWorld()->incLives();
			setVisible(false);
		}
	}
	return;
}

void Jewel::doSomething()
{
	if (isVisible())
	{
		if (getWorld()->getPlayer()->getX() == getX() && getWorld()->getPlayer()->getY() == getY())
		{
			getWorld()->increaseScore(50);
			setVisible(false);
			getWorld()->getPlayer()->obtainJewel();
			getWorld()->GameWorld::playSound(SOUND_GOT_GOODIE);
			if (getWorld()->getPlayer()->jewelsLeft() == 0)
				getWorld()->getPlayer()->obtainJewel();
		}
	}

}

void Exit::doSomething()
{
	if (isVisible())
	{
		if (getWorld()->getPlayer()->getX() == getX() && getWorld()->getPlayer()->getY() == getY())
		{
			getWorld()->GameWorld::playSound(SOUND_FINISHED_LEVEL);
			getWorld()->increaseScore(2000);
			getWorld()->increaseScore(getWorld()->getPlayer()->getBonus());
			getWorld()->getPlayer()->setToFinish();
		}
	}
}

int Player::getHpPercentage()
{
	double hp = double((m_hp * 100 )/ 20);
	int whole = hp;
	return whole;
}

void Player::reduceBonus()
{
	if (m_bonus > 0)
		m_bonus--;
	return;
}

void Player::doSomething()
{
	if (m_hp <= 0)
	{
		setDead();
		return;
	}
	int input = 0;
	Boulder* ptr;
	vector<Boulder*> listBoulders;
	for (int i = 0; i != getWorld()->getActorArray().size(); i++)
	{
		ptr = dynamic_cast<Boulder*>(getWorld()->getActorArray()[i]);
		if (ptr != nullptr)
			listBoulders.push_back(ptr);
	}
	if (this->getWorld()->getKey(input))
	{
		switch (input)
		{
		case KEY_PRESS_DOWN:
			if (getY() > 0 && getWorld()->canIMoveThere(getX(), getY() - 1))
				moveTo(getX(), getY() - 1);
			for (int i = 0; i != listBoulders.size(); i++)
			{
				if (getY() - 1 == listBoulders[i]->getY() && getX() == listBoulders[i]->getX())
					if (listBoulders[i]->moveBoulder(down))
						moveTo(getX(), getY() - 1);
			}
			setDirection(down);
			break;
		case KEY_PRESS_UP:
			if (getY() < VIEW_HEIGHT - 1 && getWorld()->canIMoveThere(getX(), getY() + 1))
				moveTo(getX(), getY() + 1);
			for (int i = 0; i != listBoulders.size(); i++)
			{
				if (getY() + 1 == listBoulders[i]->getY() && getX() == listBoulders[i]->getX())
				if (listBoulders[i]->moveBoulder(up))
					moveTo(getX(), getY() + 1);
			}
			setDirection(up);
			break;
		case KEY_PRESS_LEFT:
			if (getX() > 0 && getWorld()->canIMoveThere(getX() - 1, getY()))
				moveTo(getX() - 1, getY());
			for (int i = 0; i != listBoulders.size(); i++)
			{
				if (getY() == listBoulders[i]->getY() && getX() - 1 == listBoulders[i]->getX())
				if (listBoulders[i]->moveBoulder(left))
					moveTo(getX() - 1, getY());
			}
			setDirection(left);
			break;
		case KEY_PRESS_RIGHT:
			if (getX() < VIEW_WIDTH - 1 && getWorld()->canIMoveThere(getX() + 1, getY()))
				moveTo(getX() + 1, getY());
			for (int i = 0; i != listBoulders.size(); i++)
			{
				if (getY() == listBoulders[i]->getY() && getX() + 1 == listBoulders[i]->getX())
				if (listBoulders[i]->moveBoulder(right))
					moveTo(getX() + 1, getY());
			}
			setDirection(right);
			break;
		case KEY_PRESS_SPACE:
			if (m_bullets > 0)
			{
				shootbullet();
				getWorld()->playSound(SOUND_PLAYER_FIRE);
			}
			else if (m_bullets <= 0)
				break;
			if (getDirection() == up)
			{
				getWorld()->pushBackBullet(getX(), getY() + 1, getWorld(), up);
			}
			else if (getDirection() == right)
			{
				getWorld()->pushBackBullet(getX() + 1, getY(), getWorld(), right);
			}
			else if (getDirection() == down)
			{
				getWorld()->pushBackBullet(getX(), getY() - 1, getWorld(), down);
			}
			else if (getDirection() == left)
			{
				getWorld()->pushBackBullet(getX() - 1, getY(), getWorld(), left);
			}
			break;
		case KEY_PRESS_ESCAPE:
			setDead();
			return;
		
		}
	}
}