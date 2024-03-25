#include "GameMenu.h"

int GameMenu::FRAME_PAUSE[24] = {24, 24, 24, 25, 25, 25, 26, 26, 26, 27, 27, 27, 28, 28, 28, 29, 29, 29, 30, 30, 30, 31, 31, 31};
int GameMenu::FRAME_WIN[24] = {72, 72, 72, 72, 73, 73, 73, 73, 74, 74, 74, 74, 75, 75, 75, 75, 76, 76, 76, 76, 77, 77, 77, 77 };
int GameMenu::FRAME_OVER[24] = { 80, 80, 80, 80, 81, 81, 81, 81, 82, 82, 82, 82, 83, 83, 83, 83, 84, 84, 84, 84, 85, 85, 85, 85 };

void GameMenu::LoadSprite(int game_state)
{
	
	menuSprite = new T_Sprite(L".\\res\\monster1.png", 100, 100);
	SPRITEINFO playerInfo;
	playerInfo.Speed = 0;
	playerInfo.X = (wnd_width - 100) / 2;
	playerInfo.Y = (wnd_height - 100) / 3;
	playerInfo.Dir = DIR_LEFT;
	playerInfo.Ratio = 1.0f;
	playerInfo.Visible = true;
	menuSprite->Initiate(playerInfo);
	if (game_state == GAME_PAUSE)
	{
		menuSprite->SetSequence(FRAME_PAUSE, 24);
	}
	else if (game_state == GAME_UPGRADE)
	{
		menuSprite->SetSequence(FRAME_WIN, 24);
	}
	else if (game_state == GAME_OVER)
	{
		menuSprite->SetSequence(FRAME_OVER, 24);
	}
}
void GameMenu::UpdateSprite()
{
	if (menuSprite != NULL)
	{
		menuSprite->LoopFrame();
	}
}

GameMenu::GameMenu(HWND hWnd, int iWidth, int iHeight)
{
	m_hWnd = hWnd;
	wnd_width = iWidth;
	wnd_height = iHeight;
}

GameMenu::~GameMenu()
{
}

void GameMenu::LoadGameMenu(int game_state)
{
	int x = 0, y = 0;
	int btn_width = 0, btn_height = 0;
	Gdiplus::Color normalClr, focusClr;

	const int num_start = 4;
	wstring menuItemsStart[num_start] = { L"��ʼ", L"����", L"����", L"�˳�" };
	const int num_about = 1;
	wstring menuItemsAbout[num_about] = { L"����" };
	const int num_run = 1;
	wstring menuItemsRun[num_run] = { L"��ͣ" };
	const int num_pause = 3;
	wstring menuItemsPause[num_pause] = { L"����", L"����", L"�˳�" };
	const int num_next = 3;
	wstring menuItemsNext[num_next] = { L"��һ��", L"����", L"�˳�" };
	const int num_over = 3;
	wstring menuItemsOver[num_over] = { L"���汾��", L"����", L"�˳�" };
	const int num_win = 3;
	wstring menuItemsWin[num_win] = { L"���¿�ʼ", L"����", L"�˳�" };

	ClearItem();
	if (game_state == GAME_START)
	{
		// ���ò˵�ͼƬ
		SetMenuBkg(L".\\res\\start_menu_back.png");
		btn_width = 158; btn_height = 60;
		SetBtnBmp(L".\\res\\button.png", btn_width, btn_height);
		// ���ò˵���Ϣ
		MENU_INFO menuInfo;
		menuInfo.align = 1;				// ���뷽ʽ ����
		menuInfo.space = MENU_SPACE;	// �˵���֮����
		menuInfo.fontName = L"����";
		menuInfo.isBold = true;
		normalClr = Color::Black;
		focusClr = Color::Red;
		menuInfo.normalTextColor = normalClr;
		menuInfo.focusTextColor = focusClr;
		menuInfo.width = btn_width;
		menuInfo.height = btn_height;
		SetMenuInfo(menuInfo);
		// ���ò˵�λ��
		for (int i = 0; i < num_start; i++)
		{
			// ˮƽ�м�ƫ��25px����ֱ8/9��
			x = -25 + i*(btn_width + menuInfo.space) + (wnd_width - num_start * btn_width - (num_start - 1) * menuInfo.space) / 2;
			y = (wnd_height - btn_height) / 9 * 8;

			MENUITEM mItem;
			mItem.pos.x = x;
			mItem.pos.y = y;
			mItem.ItemName = menuItemsStart[i];
			AddMenuItem(mItem);
		}
	}
	else if (game_state == GAME_ABOUT)
	{
		// ���ò˵�ͼƬ
		SetMenuBkg(L".\\res\\about_menu_back.png");
		btn_width = 158; btn_height = 60;
		SetBtnBmp(L".\\res\\button.png", btn_width, btn_height);
		// ���ò˵���Ϣ
		MENU_INFO menuInfo;
		menuInfo.align = 1;				// ���뷽ʽ ����
		menuInfo.space = 0;	// �˵���֮����
		menuInfo.fontName = L"����";
		menuInfo.isBold = true;
		normalClr = Color::Black;
		focusClr = Color::Red;
		menuInfo.normalTextColor = normalClr;
		menuInfo.focusTextColor = focusClr;
		menuInfo.width = btn_width;
		menuInfo.height = btn_height;
		SetMenuInfo(menuInfo);
		// ���ò˵�λ��
		for (int i = 0; i < num_about; i++)
		{
			x = i*(btn_width + menuInfo.space) + (wnd_width - num_about * btn_width - (num_about - 1) * menuInfo.space) / 2;
			y = (wnd_height - btn_height) / 9 * 8;

			MENUITEM mItem;
			mItem.pos.x = x;
			mItem.pos.y = y;
			mItem.ItemName = menuItemsAbout[i];
			AddMenuItem(mItem);
		}

		if (img1 == NULL)
			img1 = new T_Graph(L".\\res\\ljs.jpg");
		if (img2 == NULL)
			img2 = new T_Graph(L".\\res\\tj.jpg");
		if (img3 == NULL)
			img3 = new T_Graph(L".\\res\\wn.jpg");
	}
	else if (game_state == GAME_HELP)
	{
		// ���ò˵�ͼƬ
		SetMenuBkg(L".\\res\\help_menu_back.png");
		btn_width = 158; btn_height = 60;
		SetBtnBmp(L".\\res\\button.png", btn_width, btn_height);
		// ���ò˵���Ϣ
		MENU_INFO menuInfo;
		menuInfo.align = 1;				// ���뷽ʽ ����
		menuInfo.space = 0;	// �˵���֮����
		menuInfo.fontName = L"����";
		menuInfo.isBold = true;
		normalClr = Color::Black;
		focusClr = Color::Red;
		menuInfo.normalTextColor = normalClr;
		menuInfo.focusTextColor = focusClr;
		menuInfo.width = btn_width;
		menuInfo.height = btn_height;
		SetMenuInfo(menuInfo);
		// ���ò˵�λ��
		for (int i = 0; i < num_about; i++)
		{
			x = i*(btn_width + menuInfo.space) + (wnd_width - num_about * btn_width - (num_about - 1) * menuInfo.space) / 2;
			y = (wnd_height - btn_height) / 9 * 8;

			MENUITEM mItem;
			mItem.pos.x = x;
			mItem.pos.y = y;
			mItem.ItemName = menuItemsAbout[i];
			AddMenuItem(mItem);
		}
	}
	else if (game_state == GAME_RUN)
	{
		// ���ò˵�ͼƬ
		//SetMenuBkg(L".\\res\\about_menu_back.png");
		btn_width = 32; btn_height = 32;
		SetBtnBmp(L".\\res\\pause.png", btn_width, btn_height);
		// ���ò˵���Ϣ
		MENU_INFO menuInfo;
		menuInfo.align = 1;				// ���뷽ʽ ����
		menuInfo.space = 0;	// �˵���֮����
		menuInfo.fontName = L"����";
		menuInfo.isBold = true;
		normalClr = Color::Black;
		focusClr = Color::Red;
		menuInfo.normalTextColor = normalClr;
		menuInfo.focusTextColor = focusClr;
		menuInfo.width = btn_width;
		menuInfo.height = btn_height;
		SetMenuInfo(menuInfo);
		// ���ò˵�λ��
		for (int i = 0; i < num_about; i++)
		{
			x = wnd_width - btn_width - 128;
			y = btn_height / 3;

			MENUITEM mItem;
			mItem.pos.x = x;
			mItem.pos.y = y;
			mItem.ItemName = L"";
			AddMenuItem(mItem);
		}
	}
	else if (game_state == GAME_PAUSE || game_state == GAME_UPGRADE || game_state == GAME_OVER || game_state == GAME_WIN)
	{
		// ���ò˵�ͼƬ
		SetMenuBkg(L".\\res\\menu_back.png");
		btn_width = 158; btn_height = 60;
		SetBtnBmp(L".\\res\\button.png", btn_width, btn_height);
		// ���ò˵���Ϣ
		MENU_INFO menuInfo;
		menuInfo.align = 1;				// ���뷽ʽ ����
		menuInfo.space = MENU_SPACE;	// �˵���֮����
		menuInfo.fontName = L"����";
		menuInfo.isBold = true;
		normalClr = Color::Black;
		focusClr = Color::Red;
		menuInfo.normalTextColor = normalClr;
		menuInfo.focusTextColor = focusClr;
		menuInfo.width = btn_width;
		menuInfo.height = btn_height;
		SetMenuInfo(menuInfo);

		if (game_state == GAME_PAUSE)
		{
			// ���ò˵�λ��
			for (int i = 0; i < num_pause; i++)
			{
				//x = (wnd_width - btn_width) / 2;
				//y = i*(btn_height + menuInfo.space) + (wnd_height - num_pause * btn_height - (num_pause - 1) * menuInfo.space) / 2;

				x = i*(btn_width + menuInfo.space) + (wnd_width - num_next * btn_width - (num_next - 1) * menuInfo.space) / 2;
				y = (wnd_height - btn_height) / 6 * 5;

				MENUITEM mItem;
				mItem.pos.x = x;
				mItem.pos.y = y;
				mItem.ItemName = menuItemsPause[i];
				AddMenuItem(mItem);
			}
			LoadSprite(GAME_PAUSE);
		}
		else if (game_state == GAME_UPGRADE)
		{
			// ���ò˵�λ��
			for (int i = 0; i < num_next; i++)
			{
				x = i*(btn_width + menuInfo.space) + (wnd_width - num_next * btn_width - (num_next - 1) * menuInfo.space) / 2;
				y = (wnd_height - btn_height) / 6 * 5;

				MENUITEM mItem;
				mItem.pos.x = x;
				mItem.pos.y = y;
				mItem.ItemName = menuItemsNext[i];
				AddMenuItem(mItem);
			}
			LoadSprite(GAME_UPGRADE);
		}
		else if (game_state == GAME_WIN)
		{
			// ���ò˵�λ��
			for (int i = 0; i < num_win; i++)
			{
				x = i*(btn_width + menuInfo.space) + (wnd_width - num_win * btn_width - (num_win - 1) * menuInfo.space) / 2;
				y = (wnd_height - btn_height) / 6 * 5;

				MENUITEM mItem;
				mItem.pos.x = x;
				mItem.pos.y = y;
				mItem.ItemName = menuItemsWin[i];
				AddMenuItem(mItem);
			}
			LoadSprite(GAME_UPGRADE);
		}
		else if (game_state == GAME_OVER)
		{
			// ���ò˵�λ��
			for (int i = 0; i < num_over; i++)
			{
				x = i*(btn_width + menuInfo.space) + (wnd_width - num_over * btn_width - (num_over - 1) * menuInfo.space) / 2;
				y = (wnd_height - btn_height) / 6 * 5;

				MENUITEM mItem;
				mItem.pos.x = x;
				mItem.pos.y = y;
				mItem.ItemName = menuItemsOver[i];
				AddMenuItem(mItem);
			}
			LoadSprite(GAME_OVER);
		}
	}
}

void GameMenu::DrawAboutText(HDC hdc)
{
	RectF infoRec;

	infoRec.Width = (REAL)256;
	infoRec.Height = (REAL)64;
	infoRec.X = (REAL)((wnd_width - infoRec.Width) / 2);
	infoRec.Y = (REAL)48;
	T_Graph::PaintText(hdc, infoRec, L"��    ��", 22, L"����", Color::White, FontStyleRegular, StringAlignmentCenter);

	infoRec.Width = (REAL)256;
	infoRec.Height = (REAL)64;
	infoRec.X = (REAL)((wnd_width - infoRec.Width) / 2);
	infoRec.Y = (REAL)140;
	T_Graph::PaintText(hdc, infoRec, L"���ƣ�����С����\t\t�汾��1.0.0", 22, L"����", Color::White, FontStyleRegular, StringAlignmentCenter);

	infoRec.Width = (REAL)200;
	infoRec.Height = (REAL)200;
	infoRec.X = (REAL)200;
	infoRec.Y = (REAL)425;
	LPCTSTR infoAuthor = L"\
						Labmem 001\n\
						���&����";
	T_Graph::PaintText(hdc, infoRec, infoAuthor, 18, L"����", Color::White, FontStyleRegular, StringAlignmentCenter);

	infoRec.Width = (REAL)200;
	infoRec.Height = (REAL)200;
	infoRec.X = (REAL)400;
	infoRec.Y = (REAL)425;
	infoAuthor = L"\
						Labmem 002\n\
						�߻�&����";
	T_Graph::PaintText(hdc, infoRec, infoAuthor, 18, L"����", Color::White, FontStyleRegular, StringAlignmentCenter);

	infoRec.Width = (REAL)200;
	infoRec.Height = (REAL)200;
	infoRec.X = (REAL)600;
	infoRec.Y = (REAL)425;
	infoAuthor = L"\
						Labmem 003\n\
						�ؿ�&��Ч";
	T_Graph::PaintText(hdc, infoRec, infoAuthor, 18, L"����", Color::White, FontStyleRegular, StringAlignmentCenter);

	img1->PaintImage(hdc, 225, 240, img1->GetImageWidth() / 2, img1->GetImageHeight() / 2, 255);
	img2->PaintImage(hdc, 225+205, 240, img2->GetImageWidth() / 2, img2->GetImageHeight() / 2, 255);
	img3->PaintImage(hdc, 225 + 205 + 205, 240, img3->GetImageWidth()/2,img3->GetImageHeight()/2, 255);
}
void GameMenu::DrawHelpText(HDC hdc)
{
	RectF infoRec;

	infoRec.Width = (REAL)256;
	infoRec.Height = (REAL)64;
	infoRec.X = (REAL)((wnd_width - infoRec.Width) / 2);
	infoRec.Y = (REAL)48;
	T_Graph::PaintText(hdc, infoRec, L"��Ϸ˵��", 22, L"����", Color::White, FontStyleRegular, StringAlignmentCenter);

	infoRec.Width = (REAL)256;
	infoRec.Height = (REAL)64;
	infoRec.X = (REAL)((wnd_width - infoRec.Width) / 2);
	infoRec.Y = (REAL)340;
	T_Graph::PaintText(hdc, infoRec, L"��������", 22, L"����", Color::White, FontStyleRegular, StringAlignmentCenter);


	infoRec.Width = (REAL)740;
	infoRec.Height = (REAL)200;
	infoRec.X = (REAL)((wnd_width - infoRec.Width) / 2);
	infoRec.Y = (REAL)120;
	LPCTSTR infoHelp = L"\
					��Ϸ��Ŀ���Ǵ�ܵ��ˣ�������һ�أ�����������Ρ�\n\
					��Ҫ�Ե����ˣ��ڴ�֮ǰ����Ҫ��ש����������Ρ�\n\
					���˻�һֱ�ε���ֱ����ʯͷ���Ρ�\n\
					��������õ�������ܹ��������������һ����";
	T_Graph::PaintText(hdc, infoRec, infoHelp, 22, L"����", Color::White, FontStyleRegular, StringAlignmentNear);

}

void GameMenu::DrawPauseText(HDC hdc)
{
	RectF infoRec;
	infoRec.Width = (REAL)256;
	infoRec.Height = (REAL)64;
	infoRec.X = (REAL)((wnd_width - infoRec.Width) / 2);
	infoRec.Y = (REAL)48;
	T_Graph::PaintText(hdc, infoRec, L"��  ͣ", 22, L"����", Color::White, FontStyleRegular, StringAlignmentCenter);
	
	menuSprite->Draw(hdc);
}

void GameMenu::DrawUpgradeText(HDC hdc, int score)
{
	RectF infoRec;
	infoRec.Width = (REAL)256;
	infoRec.Height = (REAL)64;
	infoRec.X = (REAL)((wnd_width - infoRec.Width) / 2);
	infoRec.Y = (REAL)48;
	T_Graph::PaintText(hdc, infoRec, L"��  ��", 22, L"����", Color::White, FontStyleRegular, StringAlignmentCenter);

	infoRec.Width = (REAL)256;
	infoRec.Height = (REAL)64;
	infoRec.X = (REAL)((wnd_width - infoRec.Width) / 2);
	infoRec.Y = (REAL)(wnd_height - infoRec.Height)/2 + 64;
	wchar_t info[32];
	swprintf(info, L"������%d", score);
	T_Graph::PaintText(hdc, infoRec, info, 22, L"����", Color::White, FontStyleRegular, StringAlignmentCenter);

	menuSprite->Draw(hdc);
}
void GameMenu::DrawOverText(HDC hdc, int score)
{
	RectF infoRec;
	infoRec.Width = (REAL)256;
	infoRec.Height = (REAL)64;
	infoRec.X = (REAL)((wnd_width - infoRec.Width) / 2);
	infoRec.Y = (REAL)48;
	T_Graph::PaintText(hdc, infoRec, L"ʧ  ��", 22, L"����", Color::White, FontStyleRegular, StringAlignmentCenter);

	infoRec.Width = (REAL)256;
	infoRec.Height = (REAL)64;
	infoRec.X = (REAL)((wnd_width - infoRec.Width) / 2);
	infoRec.Y = (REAL)(wnd_height - infoRec.Height) / 2 + 64;
	wchar_t info[32];
	swprintf(info, L"������%d", score);
	T_Graph::PaintText(hdc, infoRec, info, 22, L"����", Color::White, FontStyleRegular, StringAlignmentCenter);

	menuSprite->Draw(hdc);
}

void GameMenu::DrawMenu(HDC hdc, BYTE btnTrans, bool startState)
{
	int w = menu_info.width;
	int h = menu_info.height;

	int FontHeight;
	int px = 0;
	int w_px = w / (MaxMenuItemLen + 1);	//����ÿ������ռ������
	int h_px = (int)((float)(h / 2.5));
	if (w_px > h_px)
	{
		px = h_px;
	}
	else
	{
		px = w_px;
	}
	FontHeight = (px * 72) / 96;		//����ÿ���ֵ����ؼ����ֺ�

	if (isItemFocused == FALSE)
	{
		Gdiplus::RectF Rec;
		vector<MENUITEM>::iterator iter;
		for (iter = gm_menuItems.begin(); iter != gm_menuItems.end(); iter++)
		{
			int x = iter->pos.x;
			int y = iter->pos.y;

			// ���ư�ťͼ��
			if (&BtnDIB != NULL)
			{
				BtnDIB.PaintRegion(BtnDIB.GetBmpHandle(), hdc, x, y, 0, 0, w, h, 1, 0, btnTrans);
			}
			Rec.X = (float)x;
			Rec.Y = (float)y;
			Rec.Width = (float)w;
			Rec.Height = (float)h;

			// ���ư�ť����
			wstring item = iter->ItemName.c_str();
			T_Graph::PaintText(hdc, Rec, item, (REAL)FontHeight, menu_info.fontName,
				menu_info.normalTextColor, GetFontStyle(), GetAlignment());
		}
	}

	if (isItemFocused == TRUE)
	{
		int mIndex = 0;
		Gdiplus::RectF Rec;
		vector<MENUITEM>::iterator iter;
		for (iter = gm_menuItems.begin(); iter != gm_menuItems.end(); iter++)
		{
			int x = iter->pos.x;
			int y = iter->pos.y;

			Rec.X = (float)x;
			Rec.Y = (float)y;
			Rec.Width = (float)w;
			Rec.Height = (float)h;

			if (mIndex != m_index)
			{
				if (&BtnDIB != NULL)
				{
					BtnDIB.PaintRegion(BtnDIB.GetBmpHandle(), hdc, x, y, 0, 0, w, h, 1, 0, btnTrans);
				}

				wstring item = iter->ItemName.c_str();
				T_Graph::PaintText(hdc, Rec, item, (REAL)FontHeight, menu_info.fontName,
					menu_info.normalTextColor, GetFontStyle(), GetAlignment());
			}

			if (mIndex == m_index)
			{
				if (&BtnDIB != NULL)
				{
					BtnDIB.PaintRegion(BtnDIB.GetBmpHandle(), hdc, x, y, 0, h, w, h, 1, 0, btnTrans);
				}

				wstring item = iter->ItemName.c_str();
				T_Graph::PaintText(hdc, Rec, item, (REAL)FontHeight, menu_info.fontName,
					menu_info.focusTextColor, GetFontStyle(), GetAlignment());
			}

			mIndex = mIndex + 1;
		}
	}
}

void GameMenu::DrawMenu(HDC hdc, int bkgX, int bkgY, BYTE btnTrans, bool startState)
{
	if (&gm_menuBkg != NULL && startState == true)
	{
		gm_menuBkg.PaintImage(hdc, bkgX, bkgY, WIN_WIDTH, WIN_HEIGHT, bkImageAlpha);
	}
	else
	{
		T_Graph::PaintBlank(hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT, MENU_BKCLR, MENU_ALPHA);
	}
	
	int w = menu_info.width;
	int h = menu_info.height;

	int FontHeight;
	int px = 0;
	int w_px = w / (MaxMenuItemLen + 1);	//����ÿ������ռ������
	int h_px = (int)((float)(h / 2.5));
	if (w_px > h_px)
	{
		px = h_px;
	}
	else
	{
		px = w_px;
	}
	FontHeight = (px * 72) / 96;		//����ÿ���ֵ����ؼ����ֺ�

	if (isItemFocused == FALSE)
	{
		Gdiplus::RectF Rec;
		vector<MENUITEM>::iterator iter;
		for (iter = gm_menuItems.begin(); iter != gm_menuItems.end(); iter++)
		{
			int x = iter->pos.x;
			int y = iter->pos.y;

			// ���ư�ťͼ��
			if (&BtnDIB != NULL)
			{
				BtnDIB.PaintRegion(BtnDIB.GetBmpHandle(), hdc, x, y, 0, 0, w, h, 1, 0, btnTrans);
			}
			Rec.X = (float)x;
			Rec.Y = (float)y;
			Rec.Width = (float)w;
			Rec.Height = (float)h;

			// ���ư�ť����
			wstring item = iter->ItemName.c_str();
			T_Graph::PaintText(hdc, Rec, item, (REAL)FontHeight, menu_info.fontName,
				menu_info.normalTextColor, GetFontStyle(), GetAlignment());
		}
	}

	if (isItemFocused == TRUE)
	{
		int mIndex = 0;
		Gdiplus::RectF Rec;
		vector<MENUITEM>::iterator iter;
		for (iter = gm_menuItems.begin(); iter != gm_menuItems.end(); iter++)
		{
			int x = iter->pos.x;
			int y = iter->pos.y;

			Rec.X = (float)x;
			Rec.Y = (float)y;
			Rec.Width = (float)w;
			Rec.Height = (float)h;

			if (mIndex != m_index)
			{
				if (&BtnDIB != NULL)
				{
					BtnDIB.PaintRegion(BtnDIB.GetBmpHandle(), hdc, x, y, 0, 0, w, h, 1, 0, btnTrans);
				}

				wstring item = iter->ItemName.c_str();
				T_Graph::PaintText(hdc, Rec, item, (REAL)FontHeight, menu_info.fontName,
					menu_info.normalTextColor, GetFontStyle(), GetAlignment());
			}

			if (mIndex == m_index)
			{
				if (&BtnDIB != NULL)
				{
					BtnDIB.PaintRegion(BtnDIB.GetBmpHandle(), hdc, x, y, 0, h, w, h, 1, 0, btnTrans);
				}

				wstring item = iter->ItemName.c_str();
				T_Graph::PaintText(hdc, Rec, item, (REAL)FontHeight, menu_info.fontName,
					menu_info.focusTextColor, GetFontStyle(), GetAlignment());
			}

			mIndex = mIndex + 1;
		}
	}
}

void GameMenu::ClearItem()
{
	if (menuSprite != NULL)
	{
		delete menuSprite;
		menuSprite = NULL;
	}
	if (img1 != NULL)
	{
		delete img1;
		img1 = NULL;
	}
	if (img2 != NULL)
	{
		delete img1;
		img2 = NULL;
	}
	if (img3 != NULL)
	{
		delete img1;
		img3 = NULL;
	}

	gm_menuItems.clear();
}
