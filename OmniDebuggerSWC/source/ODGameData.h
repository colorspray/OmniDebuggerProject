#ifndef _ODGAMEDATA_H_
#define _ODGAMEDATA_H_

typedef struct SceneData
{
	float width;
	float height;
}SceneData;

typedef struct PlayerData
{
	float posX;
	float posY;
	bool isAlive;
}PlayerData;

typedef struct NpcData
{
	float posX;
	float posY;
	bool bFired;
	bool isAlive;
	int npcDataSize;
}NpcData;

typedef struct BulletData
{
	float posX;
	float posY;
	int bulletDataSize;
}BulletData;


typedef struct ODGameData
{
	SceneData sceneData;
	int score;
	PlayerData playerData;

	BulletData* bulletsData;
	int bulletsNumber;
	NpcData npcData[ENpcTypeMax];

}ODGameData;

#endif