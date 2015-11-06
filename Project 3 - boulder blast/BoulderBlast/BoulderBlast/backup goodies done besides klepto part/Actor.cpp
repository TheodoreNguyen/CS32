#include "Actor.h"
#include "StudentWorld.h"
#include <vector>

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

/*
void Bullet::doSomething()
{
	if (isVisible())
	{
		if (getX() == getWorld()->getPlayer()->getX() && getY() == getWorld()->getPlayer()->getY())
		{
			getWorld()->getPlayer()->damagePlayer();
			setVisible(false);
			return;
		}
		for (int i = 0; i != getWorld()->getActorArray().size(); i++)
		{
			if (getX() == getWorld()->getActorArray()[i]->getX() && getY() == getWorld()->getActorArray()[i]->getY())
			{
				if (getWorld()->getActorArray()[i]->getActorType() == IID_BOULDER)
				{
					getWorld()->getActorArray()[i]->
				}
				else if (getWorld()->getActorArray()[i]->getActorType() == IID_SNARLBOT ||
					getWorld()->getActorArray()[i]->getActorType() == IID_KLEPTOBOT ||
					getWorld()->getActorArray()[i]->getActorType() == IID_ANGRY_KLEPTOBOT)
			}


		}
	}
	return;
}
*/

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
	double hp = m_hp / 20;
	hp = 100 * hp;
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
	if (this->getWorld()->getKey(input))
	{
		switch (input)
		{
		case KEY_PRESS_DOWN:
			if (getY() > 0 && getWorld()->canIMoveThere(getX(), getY() - 1))
				moveTo(getX(), getY() - 1);
			setDirection(down);
			break;
		case KEY_PRESS_UP:
			if (getY() < VIEW_HEIGHT - 1 && getWorld()->canIMoveThere(getX(), getY() + 1))
				moveTo(getX(), getY() + 1);
			setDirection(up);
			break;
		case KEY_PRESS_LEFT:
			if (getX() > 0 && getWorld()->canIMoveThere(getX() - 1, getY()))
				moveTo(getX() - 1, getY());
			setDirection(left);
			break;
		case KEY_PRESS_RIGHT:
			if (getX() < VIEW_WIDTH - 1 && getWorld()->canIMoveThere(getX() + 1, getY()))
				moveTo(getX() + 1, getY());
			setDirection(right);
			break;
		case KEY_PRESS_ESCAPE:
			setDead();
			return;
		}
	}
}