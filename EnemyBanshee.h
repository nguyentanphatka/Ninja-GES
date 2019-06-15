#pragma once
#include "Enemy.h"

class EnemyBanshee : public Enemy 
{
private:
	float delayTime;

public:
	EnemyBanshee();
	void UpdateDistance(float dt);
	void Update(float dt);
};