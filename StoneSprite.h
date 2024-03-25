#pragma once
#include ".\BlockSprite.h"
class StoneSprite : public BlockSprite
{
public:
	bool StoneCllide(T_Scene *scene);
	bool StoneCllide(vectSpriteSet &npc_set);
	StoneSprite(wstring imgPath);
	~StoneSprite();
};