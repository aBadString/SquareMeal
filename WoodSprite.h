#pragma once
#include "BlockSprite.h"
class WoodSprite :
	public BlockSprite
{
public:
	bool StoneCllide(T_Scene *scene);
	bool StoneCllide(vectSpriteSet &npc_set);
	WoodSprite(wstring imgPath);
	~WoodSprite();
};

