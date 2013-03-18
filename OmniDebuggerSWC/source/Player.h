#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Scene.h"
#include "BulletManager.h"

//the command that the player can receive
typedef enum eplayerCommand
{
	EMoveLeft,
	EMoveRight,
	EMoveUp,
	EMoveDown,
	EMaxCommand
}ePlayerCommand;

class Player
{
private:
	float posX;
	float posY;
	float radius;
	float speed;

	// the limit that player can go in the scene
	float minPosX;
	float maxPosX;
	float minPosY;
	float maxPosY;

	bool isAlive;

	int score;

public:
	// the command list, updated from ODGame::updateCommand()
	bool commands[EMaxCommand];

public:
	Player();
	void Reset();

	void Update(float deltaTime);

	float getPosX();
	float getPosY();
	float getRadius();
	bool getAlive();

	int getScore()
	{
		return score;
	}
	void setScore(int _score)
	{
		score = _score;
	}
};

#endif