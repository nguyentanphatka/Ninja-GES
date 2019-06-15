#include "Animation.h"
#include "GameDefined.h"

void Animation::Render(float x, float y, float translateX, float translateY)
{
	if (_sprites[CurFrameIndex] != NULL)
	{
		_sprites[CurFrameIndex]->isReverse = this->isReverse;
		_sprites[CurFrameIndex]->Render(x, y, translateX, translateY);
	}
}

void Animation::Update(float dt)
{
	if (_curFrameTime > _timePerFrame)
	{
		_curFrameTime = 0;		
		if (++CurFrameIndex == _totalFrames)
		{
			isLastFrame = true;
			CurFrameIndex = 0;
		}
	}
	else
	{
		isLastFrame = false;
		_curFrameTime += dt;
	}
}

Animation::~Animation()
{
	for (auto s : _sprites)
	{
		s = nullptr;
	}
	_sprites.clear();
}

Animation::Animation(Tag tag, int index)
{
	_sprites.push_back(SpriteFactory::GetInstance()->GetSprite(tag, index));
	_totalFrames = 1;
	_timePerFrame = DEFAULT_FPS;
	CurFrameIndex = 0;
	isLastFrame = false;
}

Animation::Animation(Tag tag, int firstIndex, int lastIndex, int timePerFrame)
{
	_sprites = SpriteFactory::GetInstance()->GetSprites(tag, firstIndex, lastIndex);
	_totalFrames = _sprites.size();
	_timePerFrame = timePerFrame;
	CurFrameIndex = 0;
	isLastFrame = false;
}

Sprite * Animation::GetSprite(int i)
{
	return _sprites[i];
}