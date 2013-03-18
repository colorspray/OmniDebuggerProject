#include "Scene.h"
#include <math.h>
#include "Bullet.h"

Bullet::Bullet()
{
	radius = 16.0f;
	SPEED = 1.0f;
	posX = 0.0f;
	posY = 0.0f;
	speedX = 0.0f;
	speedY = 0.0f;
}

void Bullet::Init(float srcX, float srcY, float dstX, float dstY)
{
	posX = srcX;
	posY = srcY;

	float distanceX = dstX - srcX;
	float distanceY = dstY - srcY;
	float distance = sqrt(distanceX * distanceX + distanceY * distanceY);
	speedX = distanceX/distance * SPEED;
	speedY = distanceY/distance * SPEED;
	
	fromNpcType = ENpcTypeWest;
}

void Bullet::Update(float deltaTime)
{
	posX += deltaTime * speedX * Scene::Instance()->getWidth();
	posY += deltaTime * speedY * Scene::Instance()->getHeight();
}

bool Bullet::CheckOutofScene()
{
	if (posX < 0 || posY < 0 || posX > Scene::Instance()->getWidth() || posY > Scene::Instance()->getHeight())
	{
		return true;
	}
	return false;
}

float Bullet::getPosX()
{
	return posX;
}

float Bullet::getPosY()
{
	return posY;
}

bool Bullet::CheckIsHitPlayer(float x, float y, float r)
{
	float sqDistance = (x - posX)*(x - posX) + (y - posY)*(y - posY);
	float sqRadius = (r + radius) * (r + radius);
	return sqRadius > sqDistance;
}

bool Bullet::CheckIsHitNpc(float x, float y, float r, eNpcType e)
{
	if (e == fromNpcType)
		return false;

	float sqDistance = (x - posX)*(x - posX) + (y - posY)*(y - posY);
	float sqRadius = (r + radius) * (r + radius);
	return sqRadius > sqDistance;
}