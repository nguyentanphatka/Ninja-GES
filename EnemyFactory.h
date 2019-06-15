#pragma once
#include "Enemy.h"
#include "EnemySwordMan.h"
#include "EnemyGunMan.h"
#include "EnemyBanshee.h"
#include "EnemyBird.h"
#include "EnemyDog.h"
#include "EnemyBazokaMan.h"
#include "EnemyRunMan.h"
#include "EnemyBoss.h"

class EnemyFactory
{
public:
	EnemyFactory() {};
	~EnemyFactory() {};

	static Enemy* CreateEnemy(int enemyID)
	{
		switch (enemyID)
		{
		case 1: return new EnemySwordMan();
		case 2: return new EnemyGunMan();
		case 3: return new EnemyDog();
		case 4: return new EnemyBird();
		case 5: return new EnemyBanshee();
		case 6: return new EnemyBazokaMan();
		case 7: return new EnemyRunMan();
		case 8: return new EnemyBoss();
		default: return NULL;
		}
	}
};