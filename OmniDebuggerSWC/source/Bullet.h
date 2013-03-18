#ifndef _BULLET_H_
#define _BULLET_H_

#include "Scene.h"

typedef enum eNpcType
{
	ENpcTypeWest,
	ENpcTypeNorth,
	ENpcTypeEast,
	ENpcTypeSouth,
	ENpcTypeMax
}eNpcType;

class Bullet
{
private:
	float radius;
	float SPEED;

	float posX;
	float posY;
	float speedX;
	float speedY;

	eNpcType fromNpcType;
public:
	Bullet();
	void Init(float srcx, float srcy, float dstx, float dsty);
	void Update(float deltaTime);
	bool CheckOutofScene();
	float getPosX();
	float getPosY();
	bool CheckIsHitPlayer(float x, float y, float r);
	bool CheckIsHitNpc(float x, float y, float r, eNpcType e);

	void setFromNpcType(eNpcType e)
	{
		fromNpcType = e;
	}
};


#endif