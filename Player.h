﻿#pragma once
#include "PlayerSprite.h"
#include "PlayerState.h"
#include "PlayerStandingState.h"
#include "PlayerInjuredState.h"
#include "Item.h"
#include "Enemy.h"
#include "Bullet.h"
#include <unordered_set>

class Player : public Object
{
private:
	std::unordered_map<State, Animation*> animations;	
	static Player* _instance;
	bool DetectGround(std::unordered_set<Rect*> grounds);
	bool DetectWall(std::unordered_set<Wall*> walls);
	
public:
	Player();
	~Player();
	static Player* GetInstance();

	bool isOnGround, isOnWall;
	bool isThrowing, isAttacking;
	Rect groundBound;
	Wall wallBound;
	PlayerState* state;
	State stateName;
	Animation* curAnimation;							
	Type weaponType;
	std::unordered_map<State, bool> allow;

	void DetectSpawnY(std::unordered_set<Rect*> grounds);
	void Update(float dt, std::unordered_set<Object*> ColliableObjects);
	void CheckGroundCollision(std::unordered_set<Rect*> grounds);
	void CheckWallCollision(std::unordered_set<Wall*> walls);
	void Render(float translateX = 0, float translateY = 0);
	void OnKeyDown(int keyCode);							
	void OnKeyUp(int keyCode);							
	void ChangeState(PlayerState* newState);
};