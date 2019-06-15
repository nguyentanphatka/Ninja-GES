#include "EnemyBird.h"
#include "GameDefined.h"

EnemyBird::EnemyBird()
{
	animations[STANDING] = new Animation(ENEMY, 17, 17, DEFAULT_FPS >> 1);
	animations[RUNNING] = new Animation(ENEMY, 17, 18, DEFAULT_FPS >> 1);
	type = BIRD;
	height = ENEMY_BIRD_HEIGHT;
	width = ENEMY_BIRD_WIDTH;
	delayTime = ENEMY_BIRD_DELAY_TIME >> 1;
}

void EnemyBird::UpdateDistance(float dt)
{
	this->isReverse = (player->posX < this->posX);

	if (delayTime <= 0)
	{
		this->dx = (player->posX - this->posX) / MAX_FRAME_RATE;
		this->dy = (player->posY - this->posY) / MAX_FRAME_RATE;

		if (player->posX < this->posX)
		{
			this->dx = min(-ENEMY_BIRD_MIN_SPEEDX, dx);
		}
		else
		{
			this->dx = max(ENEMY_BIRD_MIN_SPEEDX, dx);
		}

		if (player->posY < this->posY)
		{
			this->dy = min(-ENEMY_BIRD_MIN_SPEEDY, dy);
		}
		else this->dy = max(ENEMY_BIRD_MIN_SPEEDY, dy);

		delayTime = ENEMY_BIRD_DELAY_TIME;
	}
	else
	{
		delayTime -= dt;
	}

	// stop and res
	if (dx > 0 && this->posX > player->posX)
	{
		this->dx -= 0.05f;
	}
	else if (dx < 0 && this->posX <= player->posX)
	{
		this->dx += 0.05f;
	}

	if (dy > 0 && this->posY > player->posY)
	{
		this->dy -= 0.035f;
	}
	else if (dy < 0 && this->posY <= player->posY)
	{
		this->dy += 0.035f;
	}
}

void EnemyBird::Update(float dt)
{
	Enemy::Update(dt);

	if (this->isDead)
	{
		delayTime = ENEMY_BIRD_DELAY_TIME >> 1;
	}
}

void EnemyBird::ChangeState(State StateName)
{
	switch (StateName)
	{
	case STANDING:
	{
		this->isActive = false;
		this->isDead = false;
		this->isOutScreen = false;
		break;
	}

	case RUNNING:
	{
		auto distance = player->posX - this->spawnX;

		if (activeDistance * distance > 0 && distance >= this->activeDistance)
		{
			this->dx = this->dy = 0;
			this->isActive = true;
		}
		break;
	}
	}

	this->StateName = StateName;
	this->curAnimation = animations[StateName];
}
