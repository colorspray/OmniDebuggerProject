#include "BulletManager.h"
#include <stdlib.h>

BulletManager* BulletManager::bulletManager = NULL;

BulletManager::BulletManager()
{
	bullets = new std::vector<Bullet>();
}

BulletManager* BulletManager::Instance()
{
	if (bulletManager == NULL)
	{
		bulletManager = new BulletManager();
	}
	return bulletManager;
}

void BulletManager::Update(float deltaTime)
{
	if (bullets->size() > 0)
	{
		for (std::vector<Bullet>::iterator i = bullets->begin(); i != bullets->end(); )
		{
			i->Update(deltaTime);
			if (i->CheckOutofScene())
			{
				i = bullets->erase(i);
				if (i == bullets->end())
					break;
			}
			else
			{
				++i;
			}
		}
	}
}

void BulletManager::spawnBullet(float srcx, float srcy, float dstx, float dsty, eNpcType e)
{
	Bullet newBullet;
	newBullet.Init(srcx,srcy,dstx,dsty);
	newBullet.setFromNpcType(e);
	bullets->push_back(newBullet);
}

bool BulletManager::CheckIsHitPlayer(float x, float y, float r)
{
	for (std::vector<Bullet>::iterator i = bullets->begin(); i != bullets->end(); ++i)
	{
		// if hit any bullet
		if (i->CheckIsHitPlayer(x, y, r))
		{
			return true;
		}
	}
	return false;
}

bool BulletManager::CheckIsHitNpc(float x, float y, float r, eNpcType e)
{
	for (std::vector<Bullet>::iterator i = bullets->begin(); i != bullets->end(); ++i)
	{
		// if hit any bullet
		if (i->CheckIsHitNpc(x, y, r, e))
		{
			return true;
		}
	}
	return false;
}

bool BulletManager::Reset()
{
	bullets->clear();
}
