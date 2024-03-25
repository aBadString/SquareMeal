#include "NpcSprite.h"

int NpcSprite::NPC_FRAME_DOWN[24] = { 0,0,0, 1,1,1, 2,2,3, 3,3,3, 4,4,4, 5,5,5, 6,6,6, 7,7,7 };
int NpcSprite::NPC_FRAME_LEFT_RIGHT[24] = { 8,8,8, 9,9,9, 10,10,10, 11,11,11, 12,12,12, 13,13,13, 14,14,14, 15,15,15 };
int NpcSprite::NPC_FRAME_UP[24] = { 16,16,16, 17,17,17, 18,18,18, 19,19,19, 20,20,20, 21,21,21, 22,22,22, 23,23,23 };
int NpcSprite::NPC_FRAME_GOSH[24] = {24,24,24,24, 25,25,25,25 ,26,26,26,26, 27,27,27,27, 28,28,28,28, 29,29,29,29};

void NpcSprite::Load(int score, int speed, int x, int y)
{
	SPRITEINFO spInfo;
	spInfo.Active = true;
	spInfo.Dead = false;
	spInfo.Rotation = TRANS_NONE;
	spInfo.Ratio = 0.64f;
	spInfo.Speed = speed;
	spInfo.Alpha = 255;
	spInfo.Visible = true;
	spInfo.Level = 0;
	spInfo.Score = score;
	spInfo.Dir = DIR_DOWN;
	spInfo.X = x;
	spInfo.Y = y;

	gosh = false;

	Initiate(spInfo);
	switch (spInfo.Dir)
	{
	case DIR_LEFT:
		SetSequence(NPC_FRAME_LEFT_RIGHT, 24);
		break;
	case DIR_RIGHT:
		SetSequence(NPC_FRAME_LEFT_RIGHT, 24);
		break;
	case DIR_UP:
		SetSequence(NPC_FRAME_UP, 24);
		break;
	case DIR_DOWN:
		SetSequence(NPC_FRAME_DOWN, 24);
		break;
	}
	SetLayerTypeID(LAYER_NPC);
}

void NpcSprite::UpdateDir(int dir)
{
	if (IsGosh() == true)
	{
		SetRotation(TRANS_NONE);
		SetSequence(NPC_FRAME_GOSH, 24);
	}
	else
	{
		switch (dir)
		{
		case DIR_LEFT:
			SetRotation(TRANS_NONE);
			SetSequence(NPC_FRAME_LEFT_RIGHT, 24);
			break;
		case DIR_RIGHT:
			SetRotation(TRANS_HFLIP_NOROT);
			SetSequence(NPC_FRAME_LEFT_RIGHT, 24);
			break;
		case DIR_UP:
			SetRotation(TRANS_NONE);
			SetSequence(NPC_FRAME_UP, 24);
			break;
		case DIR_DOWN:
			SetRotation(TRANS_NONE);
			SetSequence(NPC_FRAME_DOWN, 24);
			break;
		}
	}
}

NpcSprite::NpcSprite(wstring imgPath, int frameWidth, int frameHeight)
	: T_Sprite(imgPath, frameWidth, frameHeight)
{
}


NpcSprite::~NpcSprite()
{
}

void NpcSprite::Sleep(T_Scene * scene)
{
}
