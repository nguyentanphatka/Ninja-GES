#include "EnemyBanshee.h"
#include "GameDefined.h"

EnemyBanshee::EnemyBanshee()
{
	animations[STANDING] = new Animation(ENEMY, 12, 12);
	animations[RUNNING] = new Animation(ENEMY, 12, 13);
	animations[ATTACKING] = new Animation(ENEMY, 13, 14);
	type = BANSHEE;
	height = ENEMY_BANSHEE_HEIGHT;
	width = ENEMY_BANSHEE_WIDTH;
	speed = ENEMY_BANSHEE_SPEED;
	delayTime = ENEMY_BANSHEE_DELAY_TIME;
	bullets = bulletCount = BULLET_BANSHEE_COUNT;
}

void EnemyBanshee::UpdateDistance(float dt)
{
	this->isReverse = (player->posX < this->posX);
	delayTime -= dt;

	switch (this->StateName)
	{
	case RUNNING:
	{
		this->dx = vx * dt;

		if ((vx > 0 && this->posX + (this->width >> 1) >= groundBound.x + groundBound.width)
			|| (vx < 0 && this->posX - (this->width >> 1) <= groundBound.x))
		{
			this->vx = -vx;
		}

		if (delayTime <= 0)
		{
			this->ChangeState(ATTACKING);
			this->vx = -vx;
			delayTime = ENEMY_BANSHEE_DELAY_TIME;
		}
		break;
	}
	case ATTACKING:
	{
		this->dx = 0;
		break;
	}
	}
}

void EnemyBanshee::Update(float dt)
{
	Enemy::Update(dt);
	if (this->isDead)
	{
		delayTime = ENEMY_BANSHEE_DELAY_TIME;
	}
}