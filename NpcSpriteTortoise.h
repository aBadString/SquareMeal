#pragma once
#include "NpcSprite.h"
#include ".\TinyEngineCore\T_Map.h"
#include ".\My_Config.h"

class NpcSpriteTortoise :
	public NpcSprite
{
private:
	bool sleep;
	int c;
	int r;
	long time;
public:
	bool IsSleep() { return sleep; }
	void SetSleep(bool s) { sleep = s; }

	NpcSpriteTortoise(wstring imgPath, int frameWidth = 0, int frameHeight = 0);
	~NpcSpriteTortoise();
	void Sleep(T_Scene *scene);
};

