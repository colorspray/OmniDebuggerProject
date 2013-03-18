#ifndef _ODGAME_H_
#define _ODGAME_H_

#include "Scene.h"
#include "Player.h"
#include "Npc.h"
#include "ODGameData.h"
#include "Bullet.h"
#include "BulletManager.h"


class ODGame
{
private:
	ODGameData* odGameData;
	Player* player;
	Npc* npc[ENpcTypeMax];

public:
	ODGame();
	void Reset();
	ODGameData* getODGameData(); //to flash

	void UpdateCommand(int commandID, bool bcommandOn);
	void Update(float delta);
	void UpdateData();
};

#endif