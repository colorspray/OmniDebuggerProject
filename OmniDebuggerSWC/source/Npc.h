#ifndef _NPC_H_
#define _NPC_H_

#include "Scene.h"
#include "BulletManager.h"
#include "Player.h"

class Npc
{
private:
	float posX;
	float posY;
	float radius;
	float posMin;
	float posMax;
	eNpcType npcType;

	bool isWalkingClockwise;
	float speed;

	float fireInterval;
	float fireTimer;

	bool isAlive;
	float respawnTime;
	float deathTime;

	bool bFired;

	const float MIN_SPEED;
	const float MAX_SPEED;
	const float MAX_SPEEDTIME;

	Player* player;
	
public:
	
	Npc(eNpcType _type);
	void Reset();
	void SetPlayer(Player* player);
	void Update(float deltaTime);

	void setClockwise();
	void setClockwiseAs(bool isClockwise);
	float getPosX();
	float getPosY();
	float getRadius();
	bool getAlive();
	void fire();

	bool getbFired()
	{
		return bFired;
	}
	bool setbFired(bool f)
	{
		bFired = f;
	}
};

#endif