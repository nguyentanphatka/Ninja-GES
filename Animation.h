#pragma once
#include "Sprite.h"
#include "SpriteFactory.h"
#include <vector>
#include <map>
#include "GameDefined.h"

class Animation
{
private:
	int _totalFrames;						
	int _timePerFrame;						
	int _curFrameTime;						
	std::vector<Sprite*> _sprites;			

public:
	Animation() {};
	~Animation();
	Animation(Tag tag, int index);
	Animation(Tag tag, int firstIndex, int lastIndex, int timePerFrame = DEFAULT_TPS);			
	void Render(float x, float y, float translateX = 0, float translateY = 0); //render animation at location
	void Update(float dt);

	int CurFrameIndex;
	bool isLastFrame;
	bool isReverse;
	Sprite* GetSprite(int index);
};