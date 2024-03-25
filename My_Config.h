#pragma once
#include ".\TinyEngineCore\T_Sprite.h"

// С������Ϸ���е�
enum BLOCK_TYPE
{
	BLOCK_NONE,
	BLOCK_STONE,
	BLOCK_WOOD
};

#define PLAYER_NUM 1
#define TILE_SIZE 64

typedef vector<T_Sprite *> vectSpriteSet;