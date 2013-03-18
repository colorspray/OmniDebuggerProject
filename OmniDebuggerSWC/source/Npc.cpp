#include "Npc.h"
#include <stdlib.h>
#include <time.h>

Npc::Npc(eNpcType _type):
	MIN_SPEED(0.3f), MAX_SPEED(0.9f), MAX_SPEEDTIME(20.0f)
{
	npcType = _type;
	radius = 32;
	respawnTime = 3;
	
	Reset();
}

void Npc::Reset()
{
	isWalkingClockwise = true;
	speed = MIN_SPEED;
	isAlive = true;

	fireInterval = 4.0f;//4 second to shoot 
	srand (time(NULL));
	fireTimer = (float)rand() / (float)RAND_MAX * fireInterval - float(npcType); // dont'e let them shoot at the same time

	bFired = false;

	switch (npcType)
	{
	case ENpcTypeWest:
		posMin = Scene::Instance()->getBorderHeight();
		posMax = Scene::Instance()->getHeight() - Scene::Instance()->getBorderHeight() - 2 * radius;

		posX = 0;
		posY = Scene::Instance()->getHeight()/2.0f;
		break;
		
	case ENpcTypeNorth:
		posMin = Scene::Instance()->getBorderWidth();
		posMax = Scene::Instance()->getWidth() - Scene::Instance()->getBorderWidth() - 2 * radius;

		posX = Scene::Instance()->getWidth()/2.0f;
		posY = 0;
		break;

	case ENpcTypeEast:
		posMin = Scene::Instance()->getBorderHeight();
		posMax = Scene::Instance()->getHeight() - Scene::Instance()->getBorderHeight() - 2 * radius;

		posX = Scene::Instance()->getWidth() - 2 * radius;
		posY = Scene::Instance()->getHeight()/2.0f;
		break;

	case ENpcTypeSouth:
		posMin = Scene::Instance()->getBorderWidth();
		posMax = Scene::Instance()->getWidth() - Scene::Instance()->getBorderWidth() - 2 * radius;
		posX = Scene::Instance()->getWidth()/2.0f;
		posY = Scene::Instance()->getHeight() - 2 * radius;
		break;
	}
}

void Npc::Update(float deltaTime)
{
	if (speed < MAX_SPEED)
	{
		speed += (deltaTime / MAX_SPEEDTIME) * (MAX_SPEED - MIN_SPEED);
	}
	if (isAlive)
	{
		switch (npcType)
		{
		case ENpcTypeWest:
			if (isWalkingClockwise)
			{
				posY -= Scene::Instance()->getHeight() * deltaTime * speed;
				if (posY < posMin)
				{
					posY = posMin;
					setClockwise();
				}
			}
			else
			{
				posY += Scene::Instance()->getHeight() * deltaTime * speed;
				if (posY > posMax)
				{
					posY = posMax;
					setClockwise();
				}
			}
		
			break;
		
		case ENpcTypeNorth:
			if (isWalkingClockwise)
			{
				posX += Scene::Instance()->getWidth() * deltaTime * speed;
				if (posX > posMax)
				{
					posX = posMax;
					setClockwise();
				}
			}
			else
			{
				posX -= Scene::Instance()->getWidth() * deltaTime * speed;
				if (posX < posMin)
				{
					posX = posMin;
					setClockwise();
				}
			}
		
			break;

		case ENpcTypeEast:
			if (isWalkingClockwise)
			{
				posY += Scene::Instance()->getHeight() * deltaTime * speed;
				if (posY > posMax)
				{
					posY = posMax;
					setClockwise();
				}
			}
			else
			{
				posY -= Scene::Instance()->getHeight() * deltaTime * speed;
				if (posY < posMin)
				{
					posY = posMin;
					setClockwise();
				}
			}
		
			break;

		case ENpcTypeSouth:
			if (isWalkingClockwise)
			{
				posX -= Scene::Instance()->getWidth() * deltaTime * speed;
				if (posX < posMin)
				{
					posX = posMin;
					setClockwise();
				}
			}
			else
			{
				posX += Scene::Instance()->getWidth() * deltaTime * speed;
				if (posX > posMax)
				{
					posX = posMax;
					setClockwise();
				}
			}
		
			break;
		}
		if (BulletManager::Instance()->CheckIsHitNpc(posX, posY, radius, npcType))
		{
			player->setScore(player->getScore() + 1);
			isAlive = false;
			deathTime = 0.0f;
			return;
		}

		fireTimer += deltaTime;
		if (fireTimer >= fireInterval)
		{
			fireTimer = (float)rand() / (float)RAND_MAX * fireInterval / 2;
			fire();
		}
	}
	else
	{
		deathTime += deltaTime;
		if (deathTime > respawnTime)
		{
			Reset();
		}
	}
}

void Npc::setClockwiseAs(bool _isClockwise)
{
	isWalkingClockwise = _isClockwise;
}
void Npc::setClockwise()
{
	isWalkingClockwise = !isWalkingClockwise;
}

float Npc::getPosX()
{
	return posX;
}

float Npc::getPosY()
{
	return posY;
}

float Npc::getRadius()
{
	return radius;
}

bool Npc::getAlive()
{
	return isAlive;
}

void Npc::SetPlayer(Player* _player)
{
	player = _player;
}

void Npc::fire()
{
	BulletManager::Instance()->spawnBullet(posX, posY, player->getPosX(), player->getPosY(), npcType);

	bFired = true;

	if (rand() % 2)
	{
		setClockwise();
	}
}