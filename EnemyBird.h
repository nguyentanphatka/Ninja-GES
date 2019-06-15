#pragma once
#include "Enemy.h"

class EnemyBird : public Enemy 
{
private:
	float delayTime;

public:
	float activeDistance;
	EnemyBird();
	void UpdateDistance(float dt);
	void Update(float dt);
	void ChangeState(State StateName);
};