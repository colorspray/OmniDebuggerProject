#include "ODGame.h"
#include <vector>

ODGame::ODGame()
{
	player = new Player();
	odGameData = new ODGameData();
	for (int i = 0; i < ENpcTypeMax; ++i)
	{
		npc[i] = new Npc((eNpcType)i);
		npc[i]->SetPlayer(player);
	}

	Reset();
}

void ODGame::Reset()
{
	player->Reset();
	Scene::Instance()->Reset();
	for (int i = 0; i < ENpcTypeMax; ++i)
	{
		npc[i]->Reset();
	}
	BulletManager::Instance()->Reset();
	UpdateData();
}

ODGameData* ODGame::getODGameData()
{
	return odGameData;
}

void ODGame::UpdateCommand(int commandID, bool bcommandOn)
{
	if (commandID >= EMaxCommand)
		return;
	player->commands[commandID] = bcommandOn;
}

void ODGame::Update(float delta)
{
	player->Update(delta);
	for (int i = 0; i < ENpcTypeMax; ++i)
	{
		npc[i]->Update(delta);
	}
	BulletManager::Instance()->Update(delta);

	UpdateData();
}

void ODGame::UpdateData()
{
	odGameData->sceneData.width = Scene::Instance()->getWidth();
	odGameData->sceneData.height = Scene::Instance()->getHeight();

	odGameData->score = player->getScore();
	odGameData->playerData.posX = player->getPosX();
	odGameData->playerData.posY = player->getPosY();
	odGameData->playerData.isAlive = player->getAlive();

	// refresh npc info
	for (int i = 0; i < ENpcTypeMax; ++i)
	{
		odGameData->npcData[i].posX = npc[i]->getPosX();
		odGameData->npcData[i].posY = npc[i]->getPosY();
		odGameData->npcData[i].bFired = npc[i]->getbFired();
		npc[i]->setbFired(false);
		odGameData->npcData[i].isAlive = npc[i]->getAlive();
		odGameData->npcData[i].npcDataSize = sizeof(odGameData->npcData[i]);
	}

	// refresh bullets info
	std::vector<Bullet>* localBullets = BulletManager::Instance()->getBullets();
	if (odGameData->bulletsData)
	{
		delete [] odGameData->bulletsData;
		odGameData->bulletsData = NULL;
	}
	odGameData->bulletsNumber = localBullets->size();
	if (odGameData->bulletsNumber != 0)
	{
		odGameData->bulletsData = new BulletData[odGameData->bulletsNumber];
		BulletData* pbulletsData = odGameData->bulletsData;
		for (std::vector<Bullet>::iterator i = localBullets->begin(); i != localBullets->end(); ++i)
		{
			pbulletsData->posX = i->getPosX();
			pbulletsData->posY = i->getPosY();
			pbulletsData->bulletDataSize = sizeof(*pbulletsData);
			++pbulletsData;
		}
	}
}
