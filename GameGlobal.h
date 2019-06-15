#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <dinput.h>
#include <WinUser.h>
#include <unordered_map>
extern HINSTANCE hInstance;										
extern HWND hWnd;												
extern LPD3DXSPRITE spriteHandler;								
extern LPDIRECT3DDEVICE9 d3ddev;								
extern LPDIRECT3DSURFACE9 backBuffer;							
extern bool isGameRunning;										
extern bool isFrozenEnemies;
extern int frozenEnemiesTime;
extern std::unordered_map<int, bool> keyCode;

extern enum Tag
{
	PLAYER,
	ITEM,
	WEAPON,
	GROUND,
	MAP1,
	MAP2,
	MAP3,
	ENEMY,
	HOLDER,
	BULLET
};

extern enum Type
{
	NONE,
	SWORD,
	SWINGSWORD,
	SWORDMAN,
	BAZOKAMAN,
	RUNMAN,
	GUNMAN,
	DOG,
	BANSHEE,
	BIRD,
	BUTTERFLY,
	BOSS,
	DAGGER,
	EXPLODED,
	BIGEXPLODED,
	BLUESPIRIT,
	REDSPIRIT,
	GLASSHOUR,
	BLUESHURIKEN,
	REDSHURIKEN,
	BLUEBAG,
	REDBAG,
	FIREWHEEL,
	REDPOTION
};

extern enum State
{
	MOVING,
	STANDING,
	RUNNING,
	JUMPING,
	FALLING,
	SITTING,
	ATTACKING,
	ATTACKING_STAND,
	ATTACKING_SIT,
	THROWING,
	CLINGING,
	CLIMBING,
	FLYING,
	ACTIVE,
	DEAD,
	INJURED
};

struct Rect
{
	float x, y;
	float width, height;

	Rect() {}
	Rect(float x, float y, float width, float height)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

	bool IsContain(Rect r)
	{
		return !((x + width < r.x) || (x > r.x + r.width) || (y < r.y - r.height) || (y - height > r.y));
	}
};

struct Wall
{
	Rect rect;
	bool climbable;
	
	Wall() {}
	Wall(float x, float y, float width, float height, bool climbable)
	{
		this->rect.x = x;
		this->rect.y = y;
		this->rect.width = width;
		this->rect.height = height;
		this->climbable = climbable;
	}
};