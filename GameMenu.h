#pragma once
#include ".\TinyEngineCore\T_Menu.h"
#include ".\TinyEngineCore\T_Sprite.h"

class GameMenu : public T_Menu
{
private:
	HWND m_hWnd; // ´°¿Ú¾ä±ú
	int wnd_width;
	int wnd_height;
	static int FRAME_WIN[24];
	static int FRAME_PAUSE[24];
	static int FRAME_OVER[24];
	T_Sprite *menuSprite = NULL;

	T_Graph *img1 = NULL;
	T_Graph *img2 = NULL;
	T_Graph *img3 = NULL;

public:
	void LoadSprite(int game_state);

	void UpdateSprite();

	GameMenu(HWND hWnd, int iWidth, int iHeight);
	~GameMenu();
	void DrawMenu(HDC hdc, BYTE btnTrans = 255, bool startState = true);
	void DrawMenu(HDC hdc, int bkgX, int bkgY, BYTE btnTrans = 255, bool startState = true);
	void ClearItem();
	void LoadGameMenu(int game_state); // ¼ÓÔØ²Ëµ¥
	void DrawAboutText(HDC hdc);
	void DrawHelpText(HDC hdc);
	void DrawPauseText(HDC hdc);
	void DrawUpgradeText(HDC hdc, int score);
	void DrawOverText(HDC hdc, int score);
};

