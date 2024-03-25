#pragma once
#include ".\TinyEngineCore\T_Sprite.h"
#include ".\NpcSprite.h"
#include ".\TinyEngineCore\T_Scene.h"
#include ".\My_Config.h"
class BlockSprite :
	public T_Sprite
{
public:
	virtual bool StoneCllide(T_Scene *scene) = 0;
	virtual bool StoneCllide(vectSpriteSet &npc_set) = 0;
	BlockSprite(wstring imgPath);
	~BlockSprite();
};

