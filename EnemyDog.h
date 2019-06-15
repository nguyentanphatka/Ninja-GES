#pragma once
#include"Enemy.h"

class EnemyDog :public Enemy 
{
private:
	Rect curGroundBound;

public:
	float activeDistance;
	bool isOnGround;
	EnemyDog();
	~EnemyDog();
	void DetectGround(std::unordered_set<Rect*> grounds);
	void DetectCurGround(std::unordered_set<Rect*> grounds);
	void UpdateDistance(float dt);
	void ChangeState(State StateName);
};