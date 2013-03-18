#include "Player.h"

Player::Player()
{
	speed = 1.0f;
	radius = 32.0f;
	
	minPosX = Scene::Instance()->getBorderWidth();
	maxPosX = Scene::Instance()->getWidth() - Scene::Instance()->getBorderWidth() - 2*radius;
	minPosY = Scene::Instance()->getBorderHeight();
	maxPosY = Scene::Instance()->getHeight() - Scene::Instance()->getBorderHeight() - 2*radius;

	Reset();
}

void Player::Reset()
{
	score = 0;
	posX = Scene::Instance()->getWidth()/2.0f;
	posY = Scene::Instance()->getHeight()/2.0f;
	isAlive = true;
}

void Player::Update(float _delta)
{
	if (commands[EMoveLeft])
	{
		posX -= Scene::Instance()->getWidth() * speed * _delta; // run the whole width in 1s
		posX = (posX < minPosX) ? minPosX: posX;
	}
	if (commands[EMoveRight])
	{
		posX += Scene::Instance()->getWidth() * speed * _delta;
		posX = (posX > maxPosX) ? maxPosX: posX;
	}
	if (commands[EMoveUp])
	{
		posY -= Scene::Instance()->getHeight() * speed * _delta;
		posY = (posY < minPosY) ? minPosY: posY;
	}
	if (commands[EMoveDown])
	{
		posY += Scene::Instance()->getHeight() * speed * _delta;
		posY = (posY > maxPosY) ? maxPosY: posY;
	}

	if (BulletManager::Instance()->CheckIsHitPlayer(posX, posY, radius))
		isAlive = false;
}

float Player::getPosX()
{
	return posX;
}

float Player::getPosY()
{
	return posY;
}

float Player::getRadius()
{
	return radius;
}

bool Player::getAlive()
{
	return isAlive;
}