#include "Player.h"

Player* Player::_instance = NULL;

Player::Player()
{
	animations[STANDING] = new Animation(PLAYER, 0);
	animations[RUNNING] = new Animation(PLAYER, 1, 3, DEFAULT_FPS >> 1);
	animations[SITTING] = new Animation(PLAYER, 4, 4);
	animations[JUMPING] = new Animation(PLAYER, 5, 8, DEFAULT_FPS >> 2);
	animations[FALLING] = new Animation(PLAYER, 5, 8, DEFAULT_FPS >> 2);
	animations[ATTACKING_STAND] = new Animation(PLAYER, 9, 11, DEFAULT_FPS >> 1);
	animations[ATTACKING_SIT] = new Animation(PLAYER, 12, 14, DEFAULT_FPS >> 1);
	animations[CLINGING] = new Animation(PLAYER, 15);
	animations[CLIMBING] = new Animation(PLAYER, 15, 16, DEFAULT_FPS >> 1);
	animations[DEAD] = new Animation(PLAYER, 5);
	animations[INJURED] = new Animation(PLAYER, 5);
	weaponType = REDSHURIKEN;
	isOnGround = false;
	tag = PLAYER;
	width = PLAYER_WIDTH;
	height = PLAYER_STANDING_HEIGHT;
	allow[JUMPING] = true;
	allow[ATTACKING] = true;
	allow[MOVING] = true;
	allow[THROWING] = true;


}

Player::~Player()
{
	if (curAnimation) delete curAnimation;

	for (auto it = animations.begin(); it != animations.end(); ++it)
	{
		if (it->second) delete it->second;
		animations.erase(it);
	}
}

Player* Player::GetInstance()
{
	if (_instance == NULL)
		_instance = new Player();
	return _instance;
}

void Player::DetectSpawnY(std::unordered_set<Rect*> grounds)
{
	for (auto g : grounds)
	{
		if (g->x < this->posX && this->posX < g->x + g->width
			&& g->y >= groundBound.y && this->posY > g->y)
		{
			groundBound = *g;
		}
	}
	this->spawnY = this->posY = groundBound.y + (this->height >> 1);
}

void Player::Update(float dt, std::unordered_set<Object*> ColliableObjects)
{
	curAnimation->Update(dt);

	state->Update(dt);

	CollisionResult result;
	result.isCollide = false;
	result.nx = result.ny = 0;
	result.entryTime = 1.0f;

	for (auto obj : ColliableObjects)
	{
		switch (obj->tag)
		{
		case ENEMY:
		case BULLET:
		{
			CollisionResult r = Collision::GetInstance()->SweptAABB(this->GetBoundingBox(), obj->GetBoundingBox());
			if (r.isCollide)
			{
				result = r;
				break;
			}
			break;
		}

		case ITEM:
		{
			auto i = (Item*)obj;

			if (this->GetRect().IsContain(i->GetRect()))
			{
				i->isDead = true;

				switch (i->type)
				{
				case GLASSHOUR:
				{
					isFrozenEnemies = true;
					frozenEnemiesTime = ENEMY_FROZEN_TIME;
					break;
				}

				case BLUESHURIKEN:
				case FIREWHEEL:
				case REDSHURIKEN:
				{
					this->weaponType = i->type;
					break;
				}
				}
			}
		}
		}
	}

	if (!result.isCollide || stateName == INJURED)
	{
		dx = (allow[MOVING] ? vx * dt : 0);
		dy = vy * dt;
	}
	else
	{
		this->isReverse = (result.nx == 1);
		this->ChangeState(new PlayerInjuredState());
	}
}

bool Player::DetectGround(std::unordered_set<Rect*> grounds)
{
	auto rbp = this->GetRect();					//rect broading-phase
	auto bottom = rbp.y - rbp.height;
	rbp.y = rbp.y + dy;
	rbp.height = rbp.height - dy;

	if (rbp.IsContain(groundBound) && (bottom >= groundBound.y))
		return true;

	for (auto g : grounds)
	{
		if (rbp.IsContain(*g) && (bottom >= g->y))
		{
			groundBound = *g;
			return true;
		}
	}
	return false;
}

bool Player::DetectWall(std::unordered_set<Wall*> walls)
{
	bool flag = false;
	auto r = this->GetRect();
	r.x = dx > 0 ? r.x : r.x + dx;
	r.width = dx > 0 ? dx + r.width : r.width - dx;

	if (r.IsContain(wallBound.rect))
	{
		flag = true;
	}
	else
	{
		for (auto w : walls)
		{
			if (w->rect.IsContain(r))
			{
				wallBound = *w;
				flag = true;
				break;
			}
		}
	}
	return flag;
}

void Player::CheckGroundCollision(std::unordered_set<Rect*> grounds)
{
	if (this->isOnWall) return;

	if (this->vy)
	{
		this->isOnGround = false;
	}

	if (DetectGround(grounds))
	{
		if (this->vy < 0)
		{
			this->isOnGround = true;
			this->vy = this->dy = 0;
			this->posY = groundBound.y + (this->height >> 1);

			if (stateName == ATTACKING_STAND)
				this->allow[MOVING] = false;
		}
	}

	else if (!this->vy)
	{
		this->ChangeState(new PlayerFallingState());
	}
}

void Player::CheckWallCollision(std::unordered_set<Wall*> walls)
{
	if (this->isOnWall) return;

	if (this->vx && this->DetectWall(walls))
	{
		float wallLeft = wallBound.rect.x;
		float wallRight = wallLeft + wallBound.rect.width;
		float playerLeft = this->posX - (this->width >> 1);
		float playerRight = this->posX + (this->width >> 1);

		if (this->vx > 0 && playerRight > wallLeft && playerRight < wallRight)
		{
			this->vx = this->dx = 0;
			this->posX = wallLeft - (this->width >> 1);

			if (wallBound.climbable && this->vy
				&& this->posY + (this->height >> 1) <= wallBound.rect.y
				&& this->posY - (this->height >> 1) >= wallBound.rect.y - wallBound.rect.height)
			{
				this->isReverse = false;
				this->ChangeState(new PlayerClingingState());
			}
		}
		else if (this->vx < 0 && playerLeft < wallRight && playerLeft > wallLeft)
		{
			this->vx = this->dx = 0;
			this->posX = wallRight + (this->width >> 1);

			if (wallBound.climbable && this->vy
				&& this->posY + (this->height >> 1) <= wallBound.rect.y
				&& this->posY - (this->height >> 1) >= wallBound.rect.y - wallBound.rect.height)
			{
				this->isReverse = true;
				this->ChangeState(new PlayerClingingState());
			}
		}
	}
}

void Player::Render(float translateX, float translateY)
{
	auto posX = this->posX + translateX;
	auto posY = this->posY + translateY;
	camera->ConvertPositionToViewPort(posX, posY);
	curAnimation->isReverse = this->isReverse;
	curAnimation->Render(posX, posY);
}

void Player::OnKeyDown(int key)
{
	if (key == DIK_Z)
	{
		isFrozenEnemies = true;
		frozenEnemiesTime = ENEMY_FROZEN_TIME;
	}

	if (this->stateName == INJURED) return;

	switch (key)
	{
	case DIK_A:
		if (!keyCode[DIK_UP])
		{
			if (allow[ATTACKING])
			{
				allow[ATTACKING] = false;
				ChangeState(new PlayerAttackingState());
				this->isAttacking = true;
			}
		}
		else
		{
			if (allow[THROWING] && weaponType != NONE && !this->isOnWall
				&& this->stateName != ATTACKING_SIT && this->stateName != ATTACKING_STAND)
			{
				ChangeState(new PlayerAttackingState());
				this->isThrowing = true;
			}
		}
		break;

	case DIK_SPACE:
		if (allow[JUMPING])
		{
			allow[JUMPING] = false;
			ChangeState(new PlayerJumpingState());
		}
		break;
	}
}

void Player::OnKeyUp(int keyCode)
{
	if (this->stateName == INJURED) return;

	switch (keyCode)
	{
	case DIK_DOWN:
		if (stateName == SITTING)
			stateName = STANDING;
		break;
	}
}

void Player::ChangeState(PlayerState * newState)
{
	delete state;
	state = newState;
	stateName = newState->StateName;
	curAnimation = animations[stateName];
}