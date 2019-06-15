#pragma once
#include "GameGlobal.h"
#include "SpriteFactory.h"
#include "Animation.h"
#include "Collision.h"
#include "Camera.h"

class Object
{
public:
	Object() {}
	virtual ~Object() {}

	Tag tag;									
	Type type;
	float spawnX, spawnY;
	float posX, posY;							
	float vx, vy;								
	float dx, dy;
	int width, height;							
	bool isReverse;								
	bool isDead;

	Rect GetRect();
	BoundingBox GetBoundingBox();

	void Update(float dt);
	bool IsCollide(Rect r);
	virtual void Render(float translateX = 0, float translateY = 0) {}
};