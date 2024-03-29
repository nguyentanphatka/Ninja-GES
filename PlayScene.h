﻿#pragma once
#include "Scene.h"
#include "Player.h"
#include <map>
#include "Grid.h"
#include "WeaponFactory.h"
#include "BulletFactory.h"
#include "MapFactory.h"
#include "SceneManager.h"

class PlayScene : public Scene
{
private:
	Player* p;
	Map* map;
	Grid* grid;
	int level;
	float endPoint;
	std::unordered_set<Object*> visibleObjects;

public:
	PlayScene(int level);
	~PlayScene();

	bool PlayerIsOnAirGround();

	void Update(float dt);
	void UpdateScene();						
	void UpdateVisibleObjects();
	void UpdateObjects(float dt);
	void UpdatePlayer(float dt);

	void RestartScene();
	void Render();									
	void OnKeyDown(int key);						
	void OnKeyUp(int key);							
};