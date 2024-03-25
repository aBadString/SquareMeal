#include "StoneSprite.h"

StoneSprite::StoneSprite(wstring imgPath)
	:BlockSprite(imgPath)
{
}
StoneSprite::~StoneSprite()
{
}

bool StoneSprite::StoneCllide(T_Scene *scene)
{
	bool res = false;
	if (IsActive() == true && IsVisible() == true)
	{
		// 如果石头碰到地图
		if (CollideWith(scene->getBarrier()))
		{
			T_Map *map = scene->getBarrier();
			// 清除地图障碍物
			int a = 0, b = 0;
			switch (GetDir())
			{
			case DIR_LEFT:
				a = 1;
				b = 0;
				break;
			case DIR_RIGHT:
				a = -1;
				b = 0;
				break;
			case DIR_UP:
				a = 0;
				b = 1;
				break;
			case DIR_DOWN:
				a = 0;
				b = -1;
				break;
			}

			map->setTile(GetMapBlockPT().x + a, GetMapBlockPT().y + b, 4);
			SetVisible(false);
			SetActive(false);
		}
	}
	return res;
}

bool StoneSprite::StoneCllide(vectSpriteSet &npc_set)
{
	bool res = false;
	if (IsActive() == true && IsVisible() == true)
	{
		// 如果石头碰到NPC
		if (GetLayerTypeID() == LAYER_PLY_BOMB)
		{
			for (vectSpriteSet::iterator sp = npc_set.begin(); sp != npc_set.end(); sp++)
			{
				if (CollideWith((*sp)) && !((*sp)->IsDead()) && (*sp)->IsVisible() &&((NpcSprite*)(*sp))->IsGosh() == false)
				{
					(*sp)->SetActive(false);
					//(*sp)->SetVisible(false);
					//(*sp)->SetDead(true);
					((NpcSprite*)(*sp))->SetGosh(true);

					break;
				}
			}
		}
	}
	return res;
}