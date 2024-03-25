#include "PlayerSprite.h"

int PlayerSprite::PLAYER_FRAME_DOWN[24] = { 0,0,0, 1,1,1, 2,2,2, 3,3,3, 4,4,4, 5,5,5, 6,6,6, 7,7,7 };
int PlayerSprite::PLAYER_FRAME_LEFT_RIGHT[24] = { 8,8,8, 9,9,9, 10,10,10, 11,11,11, 12,12,12, 13,13,13, 14,14,14, 15,15,15};
int PlayerSprite::PLAYER_FRAME_UP[24] = {16,16,16, 17,17,17, 18,18,18, 19,19,19, 20,20,20, 21,21,21, 22,22,22, 23,23,23 };

int PlayerSprite::PLAYER_FRAME_DOWN_STONE[24] = { 48, 48, 48, 49, 49, 49, 50, 50, 50, 51, 51, 51, 52, 52, 52, 53, 53, 53, 54, 54, 54, 55, 55, 55 };
int PlayerSprite::PLAYER_FRAME_LEFT_RIGHT_STONE[24] = { 56, 56, 56, 57, 57, 57, 58, 58, 58, 59, 59, 59, 60, 60, 60, 61, 61, 61, 62, 62, 62, 63, 63, 63 };
int PlayerSprite::PLAYER_FRAME_UP_STONE[24] = { 64, 64, 64, 65, 65, 65, 66, 66, 66, 67, 67, 67, 68, 68, 68, 69, 69, 69, 70, 70, 70, 71, 71, 71 };

int PlayerSprite::PLAYER_FRAME_DOWN_MOUSE[24] = { 24, 24, 24, 25, 25, 25, 26, 26, 26, 27, 27, 27, 28, 28, 28, 29, 29, 29, 30, 30, 30, 31, 31, 31 };
int PlayerSprite::PLAYER_FRAME_LEFT_RIGHT_MOUSE[24] = { 32, 32, 32, 33, 33, 33, 34, 34, 34, 35, 35, 35, 36, 36, 36, 37, 37, 37, 38, 38, 38, 39, 39, 39 };
int PlayerSprite::PLAYER_FRAME_UP_MOUSE[24] = { 40, 40, 40, 41, 41, 41, 42, 42, 42, 43, 43, 43, 44, 44, 44, 45, 45, 45, 46, 46, 46, 47, 47, 47 };


// 获得缩放后的实际碰撞检测矩形区域
/* 重写该函数使得由于调用AdjustCollideRect()函数得到的收缩碰撞体积
 * 由原来的上下个收缩一半，变为上方收缩全部而下方不收缩
 */
inline RECT* PlayerSprite::GetCollideRect()
{
	int c_left, c_top;
	if (frameRatio>0)
	{
		c_left = (GetRatioSize().cx - colideWidth) / 2;
		//c_top = (GetRatioSize().cy - colideHeight) / 2;
		c_top = (GetRatioSize().cy - colideHeight);
	}
	else
	{
		c_left = ((int)GetWidth() - colideWidth) / 2;
		//c_top = (GetRatioSize().cy - colideHeight) / 2;
		c_top = ((int)GetHeight() - colideHeight);
	}

	colideRect.left = (LONG)X + c_left;
	colideRect.right = colideRect.left + colideWidth;
	colideRect.top = (LONG)Y + c_top;
	colideRect.bottom = colideRect.top + colideHeight;
	return &colideRect;
}

PlayerSprite::PlayerSprite(wstring imgPath, int frameWidth, int frameHeight)
	: T_Sprite(imgPath, frameWidth, frameHeight)
{
}

PlayerSprite::~PlayerSprite()
{
}

void PlayerSprite::Load(int iWidth, int iHeight)
{
	wnd_width = iWidth;
	wnd_height = iHeight;
	block = BLOCK_NONE;
	eatting = false;

	SPRITEINFO spInfo;
	spInfo.Active = false;
	spInfo.Dead = false;
	spInfo.Dir = DIR_UP;
	spInfo.Rotation = TRANS_NONE;
	spInfo.Ratio = 0.8f;
	spInfo.Level = 0;
	spInfo.Score = 0;
	spInfo.Speed = 2;
	spInfo.Alpha = 255;
	spInfo.X = 7*64;
	spInfo.Y = 6*64 - 20;
	spInfo.Visible = true;
	Initiate(spInfo);
	SetSequence(PLAYER_FRAME_DOWN, 0);
	SetLayerTypeID(LAYER_PLY);
	AdjustCollideRect(-15, -20);
}

void PlayerSprite::UpdateDir(int dir)
{
	if (block == BLOCK_NONE)
	{
		switch (dir)
		{
		case DIR_LEFT:
			SetSequence(PLAYER_FRAME_LEFT_RIGHT, 24);
			SetRotation(TRANS_NONE);
			SetDir(DIR_LEFT);
			break;
		case DIR_RIGHT:
			SetSequence(PLAYER_FRAME_LEFT_RIGHT, 24);
			SetRotation(TRANS_HFLIP_NOROT);
			SetDir(DIR_RIGHT);
			break;
		case DIR_UP:
			SetSequence(PLAYER_FRAME_UP, 24);
			SetRotation(TRANS_NONE);
			SetDir(DIR_UP);
			break;
		case DIR_DOWN:
			SetSequence(PLAYER_FRAME_DOWN, 24);
			SetRotation(TRANS_NONE);
			SetDir(DIR_DOWN);
			break;
		}
	}
	else
	{
		switch (dir)
		{
		case DIR_LEFT:
			SetSequence(PLAYER_FRAME_LEFT_RIGHT_STONE, 24);
			SetRotation(TRANS_NONE);
			SetDir(DIR_LEFT);
			break;
		case DIR_RIGHT:
			SetSequence(PLAYER_FRAME_LEFT_RIGHT_STONE, 24);
			SetRotation(TRANS_HFLIP_NOROT);
			SetDir(DIR_RIGHT);
			break;
		case DIR_UP:
			SetSequence(PLAYER_FRAME_UP_STONE, 24);
			SetRotation(TRANS_NONE);
			SetDir(DIR_UP);
			break;
		case DIR_DOWN:
			SetSequence(PLAYER_FRAME_DOWN_STONE, 24);
			SetRotation(TRANS_NONE);
			SetDir(DIR_DOWN);
			break;
		}
	}
}

void PlayerSprite::OpenMouse()
{
	switch (dir)
	{
	case DIR_LEFT:
		SetSequence(PLAYER_FRAME_LEFT_RIGHT_MOUSE, 24);
		SetRotation(TRANS_NONE);
		SetDir(DIR_LEFT);
		break;
	case DIR_RIGHT:
		SetSequence(PLAYER_FRAME_LEFT_RIGHT_MOUSE, 24);
		SetRotation(TRANS_HFLIP_NOROT);
		SetDir(DIR_RIGHT);
		break;
	case DIR_UP:
		SetSequence(PLAYER_FRAME_UP_MOUSE, 24);
		SetRotation(TRANS_NONE);
		SetDir(DIR_UP);
		break;
	case DIR_DOWN:
		SetSequence(PLAYER_FRAME_DOWN_MOUSE, 24);
		SetRotation(TRANS_NONE);
		SetDir(DIR_DOWN);
		break;
	}
}

void PlayerSprite::Stop()
{
	if (block == BLOCK_NONE)
	{
		switch (dir)
		{
		case DIR_LEFT:
			SetSequence(PLAYER_FRAME_LEFT_RIGHT, 1);
			SetRotation(TRANS_NONE);
			SetDir(DIR_LEFT);
			break;
		case DIR_RIGHT:
			SetSequence(PLAYER_FRAME_LEFT_RIGHT, 1);
			SetRotation(TRANS_HFLIP_NOROT);
			SetDir(DIR_RIGHT);
			break;
		case DIR_UP:
			SetSequence(PLAYER_FRAME_UP, 1);
			SetRotation(TRANS_NONE);
			SetDir(DIR_UP);
			break;
		case DIR_DOWN:
			SetSequence(PLAYER_FRAME_DOWN, 1);
			SetRotation(TRANS_NONE);
			SetDir(DIR_DOWN);
			break;
		}
	}
	else
	{
		switch (dir)
		{
		case DIR_LEFT:
			SetSequence(PLAYER_FRAME_LEFT_RIGHT_STONE, 1);
			SetRotation(TRANS_NONE);
			SetDir(DIR_LEFT);
			break;
		case DIR_RIGHT:
			SetSequence(PLAYER_FRAME_LEFT_RIGHT_STONE, 1);
			SetRotation(TRANS_HFLIP_NOROT);
			SetDir(DIR_RIGHT);
			break;
		case DIR_UP:
			SetSequence(PLAYER_FRAME_UP_STONE, 1);
			SetRotation(TRANS_NONE);
			SetDir(DIR_UP);
			break;
		case DIR_DOWN:
			SetSequence(PLAYER_FRAME_DOWN_STONE, 1);
			SetRotation(TRANS_NONE);
			SetDir(DIR_DOWN);
			break;
		}
	}

	LoopFrame();
	SetActive(false);
}

void PlayerSprite::SpitStone(T_Scene *scene, vector<BlockSprite *> & stone_set)
{
	if (GetBlock() == BLOCK_NONE) // 吃石头
	{
		int c = (GetX() - scene->getSceneX() + GetRatioSize().cx /2) / TILE_SIZE;
		int r = (GetY() - scene->getSceneY() + GetRatioSize().cy/2) / TILE_SIZE;

		switch (dir)
		{
		case DIR_LEFT:
			c--;
			break;
		case DIR_RIGHT:
			c++;
			break;
		case DIR_UP:
			r--;
			break;
		case DIR_DOWN:
			r++;
			break;
		}

		T_Map * map = scene->getBarrier();
		int b = map->getTile(c, r);
		switch (b)
		{
		case 3:
			SetBlock(BLOCK_WOOD);
			map->setTile(c, r, 0);
			break;
		case 4:
			SetBlock(BLOCK_STONE);
			map->setTile(c, r, 0);
			break;
		}

	}
	else // 吐石头
	{
		GAMELAYER gameLayer;
		SPRITEINFO stoneInfo;
		int m_dir = GetDir();

		int type = GetBlock();
		// 一个接口 多种实体
		switch (GetBlock())
		{
		case BLOCK_STONE:
			stone_set.push_back(new StoneSprite(L".\\res\\stone.png"));
			break;
		case BLOCK_WOOD:
			stone_set.push_back(new WoodSprite(L".\\res\\wood.png"));
			break;
		}

		
		//初始化刚增加的项目
		BlockSprite *stone = stone_set.back();
		stoneInfo.Active = true;
		stoneInfo.Dead = false;
		stoneInfo.Dir = m_dir;
		stoneInfo.Rotation = TRANS_NONE;
		stoneInfo.Ratio = 1;
		stoneInfo.Level = 0;
		stoneInfo.Score = 0;
		stoneInfo.Speed = 5;
		stoneInfo.Alpha = 255;

		/*
		switch (m_dir)
		{
		case DIR_LEFT:
			stoneInfo.X = GetX() / 64 * 64;
			stoneInfo.Y = GetY() / 64 * 64 + 64;
			break;
		case DIR_RIGHT:
			stoneInfo.X = GetX() / 64 * 64 + 64;
			stoneInfo.Y = GetY() / 64 * 64 + 64;
			break;
		case DIR_UP:
			stoneInfo.X = GetX() / 64 * 64 + 64;
			stoneInfo.Y = GetY() / 64 * 64;
			break;
		case DIR_DOWN:
			stoneInfo.X = GetX() / 64 * 64 + 64;
			stoneInfo.Y = GetY() / 64 * 64 + 64;
			break;
		}
		*/

		int c = (GetX() - scene->getSceneX() % TILE_SIZE + GetRatioSize().cx / 2) / TILE_SIZE;
		int r = (GetY() - scene->getSceneY() % TILE_SIZE + GetRatioSize().cy / 2) / TILE_SIZE;
		switch (m_dir)
		{
		case DIR_LEFT:
			c--;
			break;
		case DIR_RIGHT:
			c++;
			break;
		case DIR_UP:
			r--;
			break;
		case DIR_DOWN:
			r++;
			break;
		}
		stoneInfo.X = c * TILE_SIZE + scene->getSceneX() % TILE_SIZE;
		stoneInfo.Y = r * TILE_SIZE + scene->getSceneY() % TILE_SIZE;

		stoneInfo.Visible = true;
		stone->Initiate(stoneInfo);
		stone->AdjustCollideRect(-10, -10);

		gameLayer.layer = stone;
		if (stone_set == stone_set)
		{
			gameLayer.type_id = LAYER_PLY_BOMB;
			gameLayer.layer->SetLayerTypeID(LAYER_PLY_BOMB);
		}
		gameLayer.z_order = scene->GetTotalLayers() + 1;
		gameLayer.layer->setZorder(gameLayer.z_order);
		scene->Append(gameLayer);

		SetBlock(BLOCK_NONE);
	}
}