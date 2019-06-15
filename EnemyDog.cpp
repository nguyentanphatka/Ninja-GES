#include "EnemyDog.h"
#include "GameDefined.h"

EnemyDog::EnemyDog()
{
	animations[STANDING] = new Animation(ENEMY, 15, 15);
	animations[RUNNING] = new Animation(ENEMY, 15, 16);
	type = DOG;
	height = ENEMY_DOG_HEIGHT;
	width = ENEMY_DOG_HEIGHT;
	speed = ENEMY_DOG_HEIGHT;
}

EnemyDog::~EnemyDog()
{
}

void EnemyDog::DetectGround(std::unordered_set<Rect*> grounds)
{
	Enemy::DetectGround(grounds);
	curGroundBound = groundBound;
	isOnGround = true;
}

void EnemyDog::DetectCurGround(std::unordered_set<Rect*> grounds)
{
	Rect nextGround = curGroundBound;

	for (auto g : grounds)
	{
		if (g->y < this->posY - (this->height >> 1))
		{
			if (this->isReverse)
			{
				if (g->x <= curGroundBound.x && (nextGround.x == curGroundBound.x || g->x > nextGround.x))
				{
					nextGround = (*g);
				}
			}
			else
			{
				if (g->x >= curGroundBound.x && (nextGround.x == curGroundBound.x || g->x < nextGround.x))
				{
					nextGround = (*g);
				}
			}
		}
	}
	curGroundBound = nextGround;
}

void EnemyDog::UpdateDistance(float dt)
{
	if (this->posY - (this->height >> 1) <= this->curGroundBound.y)
	{
		this->vy = 0;
		this->posY = this->curGroundBound.y + (this->height >> 1);
	}

	this->isOnGround = (this->posX > curGroundBound.x
		&& this->posX < curGroundBound.x + curGroundBound.width);

	this->dx = vx * dt;
	this->dy = vy * dt;
}

void EnemyDog::ChangeState(State StateName)
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
			this->curGroundBound = groundBound;
			this->isOnGround = true;
			this->isActive = true;
		}
		break;
	}
	}
	this->StateName = StateName;
	this->curAnimation = animations[StateName];
}