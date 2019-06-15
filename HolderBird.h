#pragma once
#include "Holder.h"

class HolderBird : public Holder
{
public:
	HolderBird()
	{
		animation = new Animation(HOLDER, 2, 3, DEFAULT_FPS >> 1);
		type = BIRD;
		vx = vy = 0;
	}
};