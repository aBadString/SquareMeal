#pragma once
#include ".\TinyEngineCore\T_Sprite.h"
#include ".\TinyEngineCore\T_Scene.h"
#include ".\My_Config.h"
#include ".\BlockSprite.h"
#include ".\StoneSprite.h"
#include ".\WoodSprite.h"

class PlayerSprite : public T_Sprite
{
private:
	int wnd_width;
	int wnd_height;
	static int PLAYER_FRAME_UP[24];
	static int PLAYER_FRAME_DOWN[24];
	static int PLAYER_FRAME_LEFT_RIGHT[24];
	static int PLAYER_FRAME_UP_STONE[24];
	static int PLAYER_FRAME_DOWN_STONE[24];
	static int PLAYER_FRAME_LEFT_RIGHT_STONE[24];
	static int PLAYER_FRAME_UP_MOUSE[24];
	static int PLAYER_FRAME_DOWN_MOUSE[24];
	static int PLAYER_FRAME_LEFT_RIGHT_MOUSE[24];
	int block;
	bool eatting;

public:
	int GetBlock(){ return block; }
	void SetBlock(int b) { block = b; }
	void SetEatting(bool b) { eatting = b; }
	bool IsEatting() { return eatting; }

	void Load(int iWidth, int iHeight);
	void UpdateDir(int ActionType);
	void OpenMouse();
	void Stop();
	void SpitStone(T_Scene *scene, vector<BlockSprite *> &stone_set); // 吃石头吐石头
	virtual RECT* GetCollideRect();
	PlayerSprite(wstring imgPath, int frameWidth = 0, int frameHeight = 0);
	~PlayerSprite();
};

