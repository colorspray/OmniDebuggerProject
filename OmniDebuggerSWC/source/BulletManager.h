#ifndef _BULLETMANAGER_H_
#define _BULLETMANAGER_H_

#include "Bullet.h"
#include <vector>

class BulletManager
{
private:
	BulletManager();
	static BulletManager* bulletManager;

	std::vector<Bullet>* bullets;

public:
	static BulletManager* Instance();
	void Update(float deltaTime);
	void spawnBullet(float srcX, float srcY, float dstX, float dstY, eNpcType e);
	std::vector<Bullet>* getBullets()
	{
		return bullets;
	}
	bool CheckIsHitPlayer(float posX, float posY, float radius);
	bool CheckIsHitNpc(float posX, float posY, float radius, eNpcType e);
	bool Reset();
};

#endif

