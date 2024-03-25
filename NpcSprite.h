#pragma once
#include ".\TinyEngineCore\T_Sprite.h"
#include ".\TinyEngineCore\T_Scene.h"
class NpcSprite :
	public T_Sprite
{
private:
	static int NPC_FRAME_LEFT_DOWN[24];
	static int NPC_FRAME_UP[24];
	static int NPC_FRAME_DOWN[24];
	static int NPC_FRAME_LEFT_RIGHT[24];
	static int NPC_FRAME_GOSH[24];

	bool gosh;
public:
	bool IsGosh() { return gosh; }
	void SetGosh(bool g) { gosh = g; }

	void Load(int score, int speed, int x, int y);
	void UpdateDir(int dir);
	NpcSprite(wstring imgPath, int frameWidth = 0, int frameHeight = 0);
	~NpcSprite();
	virtual void Sleep(T_Scene *scene);
};

