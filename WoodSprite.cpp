#include "WoodSprite.h"

WoodSprite::WoodSprite(wstring imgPath)
	:BlockSprite(imgPath)
{
}
WoodSprite::~WoodSprite()
{
}

bool WoodSprite::StoneCllide(T_Scene *scene)
{
	bool res = false;
	if (IsActive() == true && IsVisible() == true)
	{
		// 如果木头碰到地图
		if (CollideWith(scene->getBarrier()))
		{
			SetVisible(false);
			SetActive(false);
			res = true;
		}
	}
	return res;
}

bool WoodSprite::StoneCllide(vectSpriteSet &npc_set)
{
	bool res = false;
	if (IsActive() == true && IsVisible() == true)
	{
		// 如果木头碰到NPC
		if (GetLayerTypeID() == LAYER_PLY_BOMB)
		{
			for (vectSpriteSet::iterator sp = npc_set.begin(); sp != npc_set.end(); sp++)
			{
				if (CollideWith((*sp)) && !((*sp)->IsDead()) && (*sp)->IsVisible() && ((NpcSprite*)(*sp))->IsGosh() == false)
				{
					(*sp)->SetActive(false);
					//(*sp)->SetVisible(false);
					//(*sp)->SetDead(true);
					((NpcSprite*)(*sp))->SetGosh(true);

					SetVisible(false);
					SetActive(false);

					res = true;
					break;
				}
			}
		}
	}
	return res;
}