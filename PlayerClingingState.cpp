#include "PlayerClingingState.h"

PlayerClingingState::PlayerClingingState()
{
	player->allow[CLINGING] = false;
	player->allow[ATTACKING] = false;
	player->allow[JUMPING] = false;
	player->isOnWall = true;
	player->isOnGround = false;
	player->vx = player->dx = 0;
	player->vy = player->dy = 0;
	StateName = CLINGING;
}

void PlayerClingingState::Update(float dt)
{
	this->HandleKeyboard();
}

void PlayerClingingState::HandleKeyboard()
{
	if (keyCode[DIK_C])
	{
		if (!player->isReverse && keyCode[DIK_LEFT])
		{
			player->isReverse = true;
			player->posX--;
			player->isOnWall = false;
			player->ChangeState(new PlayerJumpingState());
		}

		else if (player->isReverse && keyCode[DIK_RIGHT])
		{
			player->isReverse = false;
			player->posX++;
			player->isOnWall = false;
			player->ChangeState(new PlayerJumpingState());
		}
	}

	else if (keyCode[DIK_UP] || keyCode[DIK_DOWN])
	{
		player->ChangeState(new PlayerClimbingState());
		return;
	}
}