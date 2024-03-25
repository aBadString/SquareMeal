#include "NpcSpriteTortoise.h"



NpcSpriteTortoise::NpcSpriteTortoise(wstring imgPath, int frameWidth, int frameHeight)
	: NpcSprite(imgPath, frameWidth, frameHeight)
{
	sleep = false;
	time = 5000;
	SetStartTime(GetTickCount());
}


NpcSpriteTortoise::~NpcSpriteTortoise()
{
}

void NpcSpriteTortoise::Sleep(T_Scene *scene)
{
	if (IsGosh() == true)
	{
		return;
	}

	if (sleep == false)
	{
		SetEndTime(GetTickCount());
		if (GetEndTime() - GetStartTime() > time)
		{
			int x = (GetX() - scene->getSceneX());
			int y = (GetY() - scene->getSceneY());

			if (x%TILE_SIZE == 0 && y%TILE_SIZE == 0)
			{
				SetSleep(true);

				c = x / TILE_SIZE;
				r = y / TILE_SIZE;

				T_Map *map = scene->getBarrier();
				map->setTile(c, r, 6);
				SetVisible(false);
				SetActive(false);
				//SetPosition(c*TILE_SIZE, r*TILE_SIZE);

				SetStartTime(GetTickCount());
			}
		}
	}
	else
	{
		SetEndTime(GetTickCount());
		if (GetEndTime() - GetStartTime() > 5000)
		{
			T_Map *map = scene->getBarrier();
			map->setTile(c, r, 0);
			SetVisible(true);
			SetActive(true);
			SetSleep(false);
			SetStartTime(GetTickCount());
			time = rand() % 5000 + 5000;
		}
	}
}
