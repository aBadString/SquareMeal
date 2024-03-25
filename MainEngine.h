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
	int pass; // �ؿ�
	int npc_num;

	int wnd_width, wnd_height;  // ���ڴ�С
	int scn_width, scn_height;  // �ӿڴ�С

	static int NPC_FRAME_LEFT_DOWN[24];
	static int NPC_FRAME_UP[24];
	static int NPC_FRAME_DOWN[24];
	static int NPC_FRAME_LEFT_RIGHT[24];

	static int EXPLOSION_FRAME[8];

	static int npc_pos[90];

	AudioDX ds;
	AudioDXBuffer backmusic; // ��������
	AudioDXBuffer mousedownmusic; // ���������
	AudioDXBuffer mousemovemusic; // ��껬������

	T_Scene *scene;      // ����
	vector<BlockSprite *> stone_set; // ʯͷ
	vectSpriteSet npc_set;
	vectSpriteSet explosion_set; // ��ըЧ������
	GameMenu *gameMenu;
	PlayerSprite *player;
	
	void clear();

	void LoadMap(const char *mapName);
	void LoadNpc(int total);
	void LoadPlayer();

	void UpdateNpcPos();
	void UpdatePlayerPos(int dir);
	void UpdateStone(vector<BlockSprite *> *stone_set);
	void UpdateAnimation(); // ������Ϸ����

	int MenuClick(int index, int GameState); // ���²˵������¼�
	void BeginPass(int p);
public:
	void LoadExplosion(int x, int y); // ���ر�ըЧ��

	// ���캯��
	MainEngine(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle, WORD Icon = NULL, WORD SmIcon = NULL, int iWidth = WIN_WIDTH, int iHeight = WIN_HEIGHT);
	// ��������
	~MainEngine();
	// ��Ϸ��ʼ��
	void GameInit();
	// ��Ϸ�߼�����
	void GameLogic();
	// ��Ϸ��������
	void GameEnd();
	// ����GAME_STATEֵ��ʾ��Ϸ����
	void GamePaint(HDC hdc);
	// ����KM_ACTIONֵ��������Ϊ
	void GameKeyAction(int ActionType = KEY_SYS_NONE);
	// ����KM_ACTIONֵ���������Ϊ
	void GameMouseAction(int x, int y, int ActionType);
};

