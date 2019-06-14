#pragma once
#include "Sprite.h"
#include "PlayerSprite.h"
#include "WeaponSprite.h"
#include "EnemySprite.h"
#include "HolderSprite.h"
#include "ItemSprite.h"
#include "BulletSprite.h"

class SpriteFactory
{
private:
	static SpriteFactory* _instance;
	std::unordered_map<Tag, std::vector<Sprite*>> _sprites;		

public:
	void LoadResources();
	void AddSprite(Sprite* sprite);
	Sprite* GetSprite(Tag tag, int index);
	std::vector<Sprite*> GetSprites(Tag tag, int firstIndex, int lastIndex);
	static SpriteFactory* GetInstance();
};