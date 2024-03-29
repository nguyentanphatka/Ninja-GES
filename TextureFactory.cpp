﻿#include "TextureFactory.h"

TextureFactory* TextureFactory::_instance = NULL;

void TextureFactory::AddTexture(Tag tag, const char* filePath)
{
	_textures[tag] = (new Texture(filePath))->GetTexture();
}

void TextureFactory::LoadResources()
{
	auto textures = TextureFactory::GetInstance();
	textures->AddTexture(PLAYER, "Resources\\player.png");
	textures->AddTexture(MAP1, "Resources\\tilesmaplv1.png");
	textures->AddTexture(MAP2, "Resources\\tilesmaplv2.png");
	textures->AddTexture(MAP3, "Resources\\tilesmaplv3.png");
	textures->AddTexture(ITEM, "Resources\\item.png");
	textures->AddTexture(ENEMY, "Resources\\enemy.png");
}

TextureFactory* TextureFactory::GetInstance()
{
	if (_instance == NULL)
		_instance = new TextureFactory();
	return _instance;
}

LPDIRECT3DTEXTURE9 TextureFactory::GetTexture(Tag tag)
{
	switch (tag)
	{
	case HOLDER: case ITEM: case WEAPON:
		return _textures[ITEM];
	case ENEMY: case BULLET:
		return _textures[ENEMY];
	default:
		return _textures[tag];
	}
}