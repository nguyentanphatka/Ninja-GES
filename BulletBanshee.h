#pragma once
#include "Bullet.h"

class BulletBanshee : public Bullet
{
public:

	BulletBanshee()
	{
		activeAnimation = new Animation(BULLET, 0, 3);
		type = BANSHEE;
		height = BULLET_BANSHEE_HEIGHT;
		width = BULLET_BANSHEE_WIDTH;
		vy = BULLET_BANSHEE_JUMPING_SPEED;
		vx = BULLET_BANSHEE_SPEED;
	}

	void UpdateDistance(float dt)
	{
		this->vy -= GRAVITY_SPEED;
		//if (vy <= 0) vy = -BULLET_BANSHEE_FALLING_SPEED;
		this->dx = vx * dt;
		this->dy = vy * dt;
	}
};