﻿#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerRunningState.h"

class PlayerAttackingState : public PlayerState
{
private:
	State _curState;				
	bool _reverse;

public:
	PlayerAttackingState();
	void Update(float dt);
	void HandleKeyboard();
};