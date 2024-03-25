#pragma once
#include ".\TinyEngineCore\T_Engine.h"
#include ".\TinyEngineCore\T_Sprite.h"
#include ".\TinyEngineCore\T_Scene.h"
#include ".\TinyEngineCore\T_AI.h"
#include ".\PlayerSprite.h"
#include ".\StoneSprite.h"
#include ".\GameMenu.h"
#include ".\NpcSprite.h"
#include ".\NpcSpriteTortoise.h"
#include ".\My_Config.h"

class MainEngine : public T_Engine
{
private:
	int pass; // 关卡
	int npc_num;

	int wnd_width, wnd_height;  // 窗口大小
	int scn_width, scn_height;  // 视口大小

	static int NPC_FRAME_LEFT_DOWN[24];
	static int NPC_FRAME_UP[24];
	static int NPC_FRAME_DOWN[24];
	static int NPC_FRAME_LEFT_RIGHT[24];

	static int EXPLOSION_FRAME[8];

	static int npc_pos[90];

	AudioDX ds;
	AudioDXBuffer backmusic; // 背景音乐
	AudioDXBuffer mousedownmusic; // 鼠标点击音乐
	AudioDXBuffer mousemovemusic; // 鼠标滑过音乐

	T_Scene *scene;      // 场景
	vector<BlockSprite *> stone_set; // 石头
	vectSpriteSet npc_set;
	vectSpriteSet explosion_set; // 爆炸效果集合
	GameMenu *gameMenu;
	PlayerSprite *player;
	
	void clear();

	void LoadMap(const char *mapName);
	void LoadNpc(int total);
	void LoadPlayer();

	void UpdateNpcPos();
	void UpdatePlayerPos(int dir);
	void UpdateStone(vector<BlockSprite *> *stone_set);
	void UpdateAnimation(); // 更新游戏动画

	int MenuClick(int index, int GameState); // 按下菜单触发事件
	void BeginPass(int p);
public:
	void LoadExplosion(int x, int y); // 加载爆炸效果

	// 构造函数
	MainEngine(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle, WORD Icon = NULL, WORD SmIcon = NULL, int iWidth = WIN_WIDTH, int iHeight = WIN_HEIGHT);
	// 析构函数
	~MainEngine();
	// 游戏初始化
	void GameInit();
	// 游戏逻辑处理
	void GameLogic();
	// 游戏结束处理
	void GameEnd();
	// 根据GAME_STATE值显示游戏界面
	void GamePaint(HDC hdc);
	// 根据KM_ACTION值处理按键行为
	void GameKeyAction(int ActionType = KEY_SYS_NONE);
	// 根据KM_ACTION值处理鼠标行为
	void GameMouseAction(int x, int y, int ActionType);
};

