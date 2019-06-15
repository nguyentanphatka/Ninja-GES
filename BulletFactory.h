#pragma once
#include "BulletBanshee.h"
#include "BulletGunMan.h"
#include "BulletBazokaMan.h"
#include "BulletBoss.h"

class BulletFactory
{
public:
	static Bullet* CreateBullet(Type bulletType)
	{
		switch (bulletType)
		{
		case BANSHEE: return new BulletBanshee();
		case GUNMAN: return new BulletGunMan();
		case BAZOKAMAN: return new BulletBazokaMan();
		case BOSS: return new BulletBoss();
		}
	}
};