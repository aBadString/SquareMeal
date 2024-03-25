#include "MainEngine.h"

int MainEngine::EXPLOSION_FRAME[8] = { 0,0,1,1,2,2,3,3 };

/*
int MainEngine::NPC1_FRAME_UP[24] = { 4,4,4,4,4,4, 5,5,5,5,5,5, 6,6,6,6,6,6, 7,7,7,7,7,7 };
int MainEngine::NPC1_FRAME_DOWN[24] = { 0,0,0,0,0,0, 1,1,1,1,1,1, 2,2,2,2,2,2, 3,3,3,3,3,3 };
int MainEngine::NPC1_FRAME_LEFT_RIGHT[24] = { 8,8,8,8,8,8, 9,9,9,9,9,9, 10,10,10,10,10,10, 11,11,11,11,11,11 };
*/

int MainEngine::npc_pos[90] = {
	1,256,192,
	1,1152,192,
	1,256,1088,
	1,1152,1088,
	1,768,512,
	1,768,768,
	1,448,768,
	1,1024,768,
	1,64,576,
	1,1344,576,

	3,256,192,
	3,256,448,
	3,256,704,
	3,256,960,
	3,704,128,
	2,768,960,
	2,1216,192,
	2,1216,448,
	2,1216,704,
	2,1216,960,

	1,512,576,
	1,960,576,
	2,192,64,
	2,192,1088,
	2,1280,64,
	2,1280,1088,
	3,256,512,
	3,256,640,
	3,1216,512,
	3,1216,640,
};

void MainEngine::clear()
{
	if (scene != NULL) { delete scene; scene = NULL; }

	npc_set.clear();		npc_set.swap(vector<T_Sprite*>());
	explosion_set.clear();		explosion_set.swap(vector<T_Sprite*>());
	stone_set.clear();		stone_set.swap(vector<BlockSprite *>());
}

void MainEngine::LoadMap(const char *mapName)
{
	scene = new T_Scene();
	scene->LoadTxtMap(mapName);
	scn_width = scene->getSceneLayers()->back().layer->GetWidth();
	scn_height = scene->getSceneLayers()->back().layer->GetHeight();
	// 视图初始位置以地图作为参照
	int scn_x = (wnd_width - scn_width) / 2;
	int scn_y = (wnd_height - scn_height) / 2;
	// 将地图初始化为屏幕中央位置
	scene->InitScene(scn_x, scn_y, scn_width, scn_height, wnd_width, wnd_height);
	// 将所有地图图层定位到屏幕中央
	for (SCENE_LAYERS::iterator p = scene->getSceneLayers()->begin(); p != scene->getSceneLayers()->end(); p++)
	{
		if (p->layer->ClassName() == "T_Map")
		{
			p->layer->SetPosition(scn_x, scn_y);
		}
	}
}
void MainEngine::LoadNpc(int total)
{
	for (int i = 0; i < total; ++i)
	{
		NpcSprite *sp;
		int type = npc_pos[(pass - 1) * 30 + 3 * i];
		int speed = 2;
		if (type == 1)
		{
			sp = new NpcSprite(L".\\res\\npc1.png", 100, 100);
		}
		else if (type == 2)
		{
			sp = new NpcSprite(L".\\res\\npc2.png", 100, 100);
			speed = 3;
		}
		else if (type == 3)
		{
			sp = new NpcSpriteTortoise(L".\\res\\npc3.png", 100, 100);
		}
		sp->Load(100*type, speed,
			npc_pos[(pass - 1) * 30 + 3 * i + 1] + scene->getSceneX(),
			npc_pos[(pass - 1) * 30 + 3 * i + 2] + scene->getSceneY()
		);

		GAMELAYER gameLayer;
		gameLayer.layer = sp;
		gameLayer.type_id = LAYER_NPC;
		gameLayer.z_order = scene->getSceneLayers()->size() + 1;
		gameLayer.layer->setZorder(gameLayer.z_order);
		scene->Append(gameLayer);

		npc_set.push_back(sp);
	}
}
void MainEngine::LoadPlayer()
{
	player = new PlayerSprite(L".\\res\\monster1.png", 100, 100);
	player->Load(wnd_width, wnd_height);

	GAMELAYER gameLayer;
	gameLayer.layer = player;
	gameLayer.type_id = LAYER_PLY;
	gameLayer.z_order = scene->getSceneLayers()->size() + 1;
	gameLayer.layer->setZorder(gameLayer.z_order);
	scene->Append(gameLayer);
//	tongue = new T_Sprite(".\\res\\tongue.png", 15, 15);

}
void MainEngine::LoadExplosion(int x, int y)
{
	SPRITEINFO explInfo;
	GAMELAYER gameLayer;

	explosion_set.push_back(new T_Sprite(L".\\res\\explosion.png", 128, 128));
	// 初始化刚增加的项目
	T_Sprite *sp_explosion = explosion_set.back();

	explInfo.Active = true;
	explInfo.Dead = false;
	explInfo.Dir = 0;
	explInfo.Rotation = TRANS_NONE;
	explInfo.Ratio = 1;
	explInfo.Level = 0;
	explInfo.Score = 0;
	explInfo.Speed = 5;
	explInfo.Alpha = 255;
	explInfo.X = x;
	explInfo.Y = y;
	explInfo.Visible = true;


	sp_explosion->Initiate(explInfo);
	sp_explosion->SetSequence(EXPLOSION_FRAME, 8);
	sp_explosion->SetLayerTypeID(LAYER_EXPLOSION);

	gameLayer.layer = sp_explosion;
	gameLayer.type_id = LAYER_EXPLOSION;
	gameLayer.z_order = scene->getSceneLayers()->size() + 1;
	gameLayer.layer->setZorder(gameLayer.z_order);
	scene->Append(gameLayer);
}

void MainEngine::UpdatePlayerPos(int dir)
{
	int nextStepX, nextStepY;
	int SpeedX = 0, SpeedY = 0;
	if (player->IsVisible() == true && player->IsActive() == true)
	{
		switch (dir)
		{
		case DIR_LEFT:
			SpeedX = -player->GetSpeed();
			SpeedY = 0;
			nextStepX = player->GetX() - player->GetSpeed();
			if (nextStepX <= 0)
				SpeedX = 0 - player->GetX();
			break;
		case DIR_RIGHT:
			SpeedX = player->GetSpeed();
			SpeedY = 0;
			nextStepX = player->GetX() + player->GetRatioSize().cx + player->GetSpeed();
			if (nextStepX >= wnd_width)
				SpeedX = wnd_width - player->GetRatioSize().cx - player->GetX();
			break;
		case DIR_UP:
			SpeedX = 0;
			SpeedY = -player->GetSpeed();
			nextStepY = player->GetY() - player->GetSpeed();
			if (nextStepY <= 0)
				SpeedY = 0 - player->GetY();
			break;
		case DIR_DOWN:
			SpeedX = 0;
			SpeedY = player->GetSpeed();
			nextStepY = player->GetY() + player->GetRatioSize().cy + player->GetSpeed();
			if (nextStepY >= wnd_height)
				SpeedY = wnd_height - player->GetRatioSize().cy - player->GetY();
			break;
		}
		player->Move(SpeedX, SpeedY);

		int x = player->GetX();
		int y = player->GetY();
		if (!player->CollideWith(scene->getBarrier()))
			player->Move(SpeedX, SpeedY);
		if (player->CollideWith(scene->getBarrier()))
			player->SetPosition(x, y);
	}

	if (player->IsEatting() == true && player->IsVisible() == true && player->IsActive() == false)
	{
		player->OpenMouse();
		if (player->LoopFrameOnce())
		{
			player->SpitStone(scene, stone_set);
			player->SetEatting(false);
		}
	}

	// 处理与NPC碰撞
	vectSpriteSet::iterator p;
	for (p = npc_set.begin(); p != npc_set.end(); p++)
	{
		if (player->CollideWith((*p)) && !(*p)->IsDead() && (*p)->IsVisible())
		{
			if (((NpcSprite*)(*p))->IsGosh() == true)
			{
				(*p)->SetVisible(false);
				(*p)->SetDead(true);
				player->SetScore(player->GetScore() + (*p)->GetScore());
			}
			else if (((NpcSprite*)(*p))->IsGosh() == false)
			{
				GameState = GAME_OVER;
				gameMenu->LoadGameMenu(GAME_OVER);
				gameMenu->SetClickSound(&mousedownmusic);
				gameMenu->SetMoveSound(&mousemovemusic);
			}
		}
	}
}
void MainEngine::UpdateStone(vector<BlockSprite *> *stone_set)
{
	if (stone_set->size() == 0)
	{
		return;
	}
	for (vector<BlockSprite *>::iterator itp = stone_set->begin(); itp != stone_set->end(); )
	{
		if ((*itp)->IsVisible() == true && (*itp)->IsActive() == true)
		{
			int SpeedX = 0, SpeedY = 0;
			switch ((*itp)->GetDir())
			{
			case DIR_LEFT:
				SpeedX = -(*itp)->GetSpeed();
				SpeedY = 0;
				break;
			case DIR_RIGHT:
				SpeedX = (*itp)->GetSpeed();
				SpeedY = 0;
				break;
			case DIR_UP:
				SpeedX = 0;
				SpeedY = -(*itp)->GetSpeed();
				break;
			case DIR_DOWN:
				SpeedX = 0;
				SpeedY = (*itp)->GetSpeed();
				break;
			}
			(*itp)->Move(SpeedX, SpeedY);

			// 检查石头是否击中目标
			if ((*itp)->StoneCllide(npc_set))
			{
				LoadExplosion((*itp)->GetX()-32, (*itp)->GetY() - 32);
			}
			if((*itp)->StoneCllide(scene))
			{
				LoadExplosion((*itp)->GetX() - 32, (*itp)->GetY() - 32);
			}
			if (GameState != GAME_RUN)
			{
				return;
			}
		}

		// 炮弹移除场景或者消失时，删除炮弹
		if ((*itp)->IsVisible() == false
			/*
			|| (*itp)->GetY() < 0 || (*itp)->GetX() < 0
			|| (*itp)->GetY() > wnd_height || (*itp)->GetX() > wnd_width*/
			)
		{
			for (SCENE_LAYERS::iterator p = scene->getSceneLayers()->begin(); p != scene->getSceneLayers()->end(); p++)
			{
				if ((*p).layer == (*itp))
				{
					p = scene->getSceneLayers()->erase(p);
					break;
				}
			}
			delete (*itp);
			itp = stone_set->erase(itp);
		}
		
		if (itp == stone_set->end())
		{
			break;
		}
		itp++;
	}
}
void MainEngine::UpdateNpcPos()
{
	if (npc_set.size() == 0)
		return;

	T_AI *spAi = new T_AI(4);
	vectSpriteSet::iterator p;
	for (p = npc_set.begin(); p != npc_set.end(); p++)
	{
		if ((*p)->IsDead() == false)
		{
			int npc_dir = (*p)->GetDir();
			((NpcSprite*)(*p))->UpdateDir(npc_dir);
			if ((*p)->IsVisible() == true && (*p)->IsActive() == true)
			{
				/*
				for (int i = 0; i < PLAYER_NUM; ++i)
				{
					spAi->Evade((*p), player[i]); // 躲避玩家
				}
				*/
				spAi->CheckOverlay((*p), npc_set); // 防止重叠

				// 玩家碰撞处理
				if ((*p)->CollideWith(player) && (*p)->IsDead() == false && (*p)->IsVisible() && ((NpcSprite*)(*p))->IsGosh() == false)
				{
					GameState = GAME_OVER;
					gameMenu->LoadGameMenu(GAME_OVER);
					gameMenu->SetClickSound(&mousedownmusic);
					gameMenu->SetMoveSound(&mousemovemusic);
				}
				// NPC 自由漫游
				spAi->Wander((*p), npc_dir, (*p)->GetSpeed(), scene->getBarrier());
			}
			((NpcSprite*)(*p))->Sleep(scene);
		}
	}
	delete spAi;
}
void MainEngine::UpdateAnimation()
{
	if (npc_set.size() > 0)
	{
		for (vectSpriteSet::iterator p = npc_set.begin(); p != npc_set.end(); p++)
		{
			(*p)->LoopFrame();
		}
	}
	for (int i = 0; i < PLAYER_NUM; ++i)
	{
		if (player != NULL)
		{
			if (player->IsVisible() == true && player->IsActive() == true)
			{
				player->LoopFrame();
			}
		}
	}
	if (explosion_set.size()>0)
	{
		vectSpriteSet::iterator e = explosion_set.begin();
		for (; e != explosion_set.end();)
		{
			if ((*e)->LoopFrameOnce() == true)
			{
				// 删除场景中已经失效的爆炸对象	
				SCENE_LAYERS::iterator lp;
				for (lp = scene->getSceneLayers()->begin(); lp != scene->getSceneLayers()->end(); lp++)
				{
					if ((*lp).layer == (*e))
					{
						lp = scene->getSceneLayers()->erase(lp);
						break;
					}
				}
				delete (*e);
				e = explosion_set.erase(e);
				continue;
			}
			else
			{
				++e;
			}
		}
	}
}

MainEngine::MainEngine(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle, WORD Icon, WORD SmIcon, int iWidth, int iHeight)
	: T_Engine(hInstance, szWindowClass, szTitle, Icon, SmIcon, iWidth, iHeight) // 调用父类带参数的构造方法
{
	wnd_width = iWidth;
	wnd_height = iHeight;
}

MainEngine::~MainEngine()
{
}

// 游戏结束处理
void MainEngine::GameEnd()
{
	clear();
	gameMenu->DestroyAll();
}
// 游戏初始化
void MainEngine::GameInit()
{
	GameState = GAME_START;
	gameMenu = new GameMenu(m_hWnd, wnd_width, wnd_height);
	gameMenu->LoadGameMenu(GAME_START);
	gameMenu->SetClickSound(&mousedownmusic);
	gameMenu->SetMoveSound(&mousemovemusic);

	if (ds.CreateDS(m_hWnd))
	{
		backmusic.LoadWave(ds, L".\\res\\backmusic.wav");
		mousedownmusic.LoadWave(ds, L".\\res\\mousedown.wav");
		mousemovemusic.LoadWave(ds, L".\\res\\mousemove.wav");
		backmusic.Play(true);
	}
}
// 游戏逻辑处理
void MainEngine::GameLogic()
{
	if (GameState == GAME_RUN)
	{
		GameKeyAction();  // 处理快速游戏按键
		UpdatePlayerPos(player->GetDir());
		UpdateNpcPos();
		UpdateStone(&stone_set);
		UpdateAnimation();
		scene->ScrollScene(player);

		// 计算场上活着的怪物
		int n = 0;
		for (vectSpriteSet::iterator p = npc_set.begin(); p != npc_set.end(); p++)
		{
			if ((*p)->IsDead() == false)
			{
				n++;
			}
		}
		npc_num = n;
		if (npc_num <= 0)
		{
			if (pass < 3)
			{
				GameState = GAME_UPGRADE;
				gameMenu->LoadGameMenu(GAME_UPGRADE);
				gameMenu->SetClickSound(&mousedownmusic);
				gameMenu->SetMoveSound(&mousemovemusic);
			}
			else
			{
				GameState = GAME_WIN;
				gameMenu->LoadGameMenu(GAME_WIN);
				gameMenu->SetClickSound(&mousedownmusic);
				gameMenu->SetMoveSound(&mousemovemusic);
			}
		}
	}
	else if (GameState == GAME_PAUSE || GameState == GAME_UPGRADE || GameState == GAME_OVER || GameState == GAME_WIN)
	{
		gameMenu->UpdateSprite();
	}
}
// 根据GAME_STATE值显示游戏界面
void MainEngine::GamePaint(HDC hdc)
{
	if (GameState == GAME_START)
	{
		gameMenu->T_Menu::DrawMenu(hdc);
	}
	else if (GameState == GAME_ABOUT)
	{
		gameMenu->T_Menu::DrawMenu(hdc);
		gameMenu->DrawAboutText(hdc);
	}
	else if (GameState == GAME_HELP)
	{
		gameMenu->T_Menu::DrawMenu(hdc);
		gameMenu->DrawHelpText(hdc);
	}
	else if (GameState == GAME_RUN)
	{
		scene->Draw(hdc, 0, 0);
		gameMenu->DrawMenu(hdc);

		RectF infoRec;
		infoRec.Width = (REAL)512;
		infoRec.Height = (REAL)48;
		infoRec.X = (REAL)(10);
		infoRec.Y = (REAL)(0);

		wchar_t info[32];
		swprintf(info, L"分数：%d  关卡：%d  怪物：%d", player->GetScore(), pass, npc_num);
		T_Graph::PaintText(hdc, infoRec, info, 22, L"楷体", Color::White, FontStyleRegular, StringAlignmentCenter);

	}
	else if (GameState == GAME_PAUSE)
	{
		scene->Draw(hdc, 0, 0);
		gameMenu->DrawMenu(hdc, 0, 0);
		gameMenu->DrawPauseText(hdc);
	}
	else if (GameState == GAME_UPGRADE)
	{
		scene->Draw(hdc, 0, 0);
		gameMenu->DrawMenu(hdc, 0, 0);
		gameMenu->DrawUpgradeText(hdc, player->GetScore());
	}
	else if (GameState == GAME_WIN)
	{
		scene->Draw(hdc, 0, 0);
		gameMenu->DrawMenu(hdc, 0, 0);
		gameMenu->DrawUpgradeText(hdc, player->GetScore());
	}
	else if (GameState == GAME_OVER)
	{
		scene->Draw(hdc, 0, 0);
		gameMenu->DrawMenu(hdc, 0, 0);
		gameMenu->DrawOverText(hdc, player->GetScore());
	}
}
// 根据KM_ACTION值处理按键行为
void MainEngine::GameKeyAction(int ActionType)
{
	if (GameState == GAME_START || GameState == GAME_ABOUT || GameState == GAME_HELP || GameState == GAME_PAUSE || GameState == GAME_UPGRADE || GameState == GAME_OVER || GameState == GAME_WIN)
	{
		if (GetAsyncKeyState(VK_UP) < 0)
		{
			gameMenu->MenuKeyDown(VK_UP);
		}
		if (GetAsyncKeyState(VK_DOWN) < 0)
		{
			gameMenu->MenuKeyDown(VK_DOWN);
		}
		if (GetAsyncKeyState(VK_LEFT) < 0)
		{
			gameMenu->MenuKeyDown(VK_LEFT);
		}
		if (GetAsyncKeyState(VK_RIGHT) < 0)
		{
			gameMenu->MenuKeyDown(VK_RIGHT);
		}
		if (GetAsyncKeyState(VK_RETURN) < 0)
		{
			int index = gameMenu->GetMenuIndex();
			GameState = MenuClick(index, GameState);
		}
	}
	else if (GameState == GAME_RUN)
	{
		if (ActionType == KEY_DOWN)
		{
			if (CheckKey(VK_LEFT) && !CheckKey(VK_DOWN) && !CheckKey(VK_UP))
			{
				if (player->IsEatting() == false)
				{
					player->SetActive(true);
					player->UpdateDir(DIR_LEFT);
				}
			}
			if (CheckKey(VK_RIGHT) && !CheckKey(VK_DOWN) && !CheckKey(VK_UP))
			{
				if (player->IsEatting() == false)
				{
					player->SetActive(true);
					player->UpdateDir(DIR_RIGHT);
				}
			}
			if (CheckKey(VK_UP) && !CheckKey(VK_LEFT) && !CheckKey(VK_RIGHT))
			{
				if (player->IsEatting() == false)
				{
					player->SetActive(true);
					player->UpdateDir(DIR_UP);
				}
			}
			if (CheckKey(VK_DOWN) && !CheckKey(VK_LEFT) && !CheckKey(VK_RIGHT))
			{
				if (player->IsEatting() == false)
				{
					player->SetActive(true);
					player->UpdateDir(DIR_DOWN);
				}
			}
			// 按下空格
			if (CheckKey(VK_SPACE))
			{
				if (player->IsDead() == false && player->IsVisible() == true)
				{
					player->SetEatting(true);
				}
			}
			/*
			0x57 W
			0x41 A
			0x53 S
			0x44 D
			*/
			if (CheckKey(0x57))
			{
				player->SetBlock(BLOCK_WOOD);
			}
			if (CheckKey(0x53))
			{
				player->SetBlock(BLOCK_STONE);
			}
			if (CheckKey(0x41))
			{
				vectSpriteSet::iterator p;
				for (p = npc_set.begin(); p != npc_set.end(); p++)
				{
					(*p)->SetDead(true);
				}
			}
			if (CheckKey(0x44))
			{
				GameState = GAME_OVER;
				gameMenu->LoadGameMenu(GAME_OVER);
			}
			
			/*
			if (CheckKey(0x41) && !CheckKey(0x53) && !CheckKey(0x57))
			{
				player[1]->SetActive(true);
				player[1]->UpdateDir(DIR_LEFT);
			}
			if (CheckKey(0x44) && !CheckKey(0x53) && !CheckKey(0x57))
			{
				player[1]->SetActive(true);
				player[1]->UpdateDir(DIR_RIGHT);
			}
			if (CheckKey(0x57) && !CheckKey(0x41) && !CheckKey(0x44))
			{
				player[1]->SetActive(true);
				player[1]->UpdateDir(DIR_UP);
			}
			if (CheckKey(0x53) && !CheckKey(0x41) && !CheckKey(0x44))
			{
				player[1]->SetActive(true);
				player[1]->UpdateDir(DIR_DOWN);
			}
			*/
		}
		else if(ActionType == KEY_UP)
		{/*
			if (CheckKey(VK_LEFT) || CheckKey(VK_RIGHT) || CheckKey(VK_UP) || CheckKey(VK_DOWN))
			{
				player[0]->Stop();
			}
			if (CheckKey(0x41) || CheckKey(0x44) || CheckKey(0x57) || CheckKey(0x53))
			{
				player[1]->Stop();
			}*/
			player->Stop();
		}
	}
}
// 根据KM_ACTION值处理鼠标行为
void MainEngine::GameMouseAction(int x, int y, int ActionType)
{
	if (GameState == GAME_START || GameState == GAME_ABOUT || GameState == GAME_HELP || GameState == GAME_RUN || GameState == GAME_PAUSE || GameState == GAME_UPGRADE || GameState == GAME_OVER || GameState == GAME_WIN)
	{
		if (ActionType == MOUSE_MOVE)
		{
			gameMenu->MenuMouseMove(x, y);
		}
		else if (ActionType == MOUSE_LCLICK)
		{
			int index = gameMenu->MenuMouseClick(x, y);
			GameState = MenuClick(index, GameState);
		}
	}
}

int MainEngine::MenuClick(int index, int GameState)
{
	int game_state = GameState;
	if (index >= 0)
	{
		if (game_state == GAME_START)
		{
			switch (index)
			{
			case 0: // 开始
				game_state = GAME_RUN;
				BeginPass(1);
				break;
			case 1: // 帮助
				game_state = GAME_HELP;
				gameMenu->LoadGameMenu(GAME_HELP);
				gameMenu->SetClickSound(&mousedownmusic);
				gameMenu->SetMoveSound(&mousemovemusic);
				break;
			case 2: // 关于
				game_state = GAME_ABOUT;
				gameMenu->LoadGameMenu(GAME_ABOUT);
				gameMenu->SetClickSound(&mousedownmusic);
				gameMenu->SetMoveSound(&mousemovemusic);
				break;
			case 3: // 退出
				SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
				break;
			}
		}
		else if (game_state == GAME_ABOUT)
		{
			switch (index)
			{
			case 0: // 返回
				game_state = GAME_START;
				gameMenu->LoadGameMenu(GAME_START);
				gameMenu->SetClickSound(&mousedownmusic);
				gameMenu->SetMoveSound(&mousemovemusic);
				break;
			}
		}
		else if (game_state == GAME_HELP)
		{
			switch (index)
			{
			case 0: // 返回
				game_state = GAME_START;
				gameMenu->LoadGameMenu(GAME_START);
				gameMenu->SetClickSound(&mousedownmusic);
				gameMenu->SetMoveSound(&mousemovemusic);
				break;
			}
		}
		else if (game_state == GAME_RUN)
		{
			switch (index)
			{
			case 0: // 暂停
				game_state = GAME_PAUSE;
				gameMenu->LoadGameMenu(GAME_PAUSE);
				gameMenu->SetClickSound(&mousedownmusic);
				gameMenu->SetMoveSound(&mousemovemusic);
				break;
			}
		}
		else if (game_state == GAME_PAUSE)
		{
			switch (index)
			{
			case 0: // 继续
				game_state = GAME_RUN;
				gameMenu->LoadGameMenu(GAME_RUN);
				gameMenu->SetClickSound(&mousedownmusic);
				gameMenu->SetMoveSound(&mousemovemusic);
				break;
			case 1: // 返回
				clear();
				game_state = GAME_START;
				gameMenu->LoadGameMenu(GAME_START);
				gameMenu->SetClickSound(&mousedownmusic);
				gameMenu->SetMoveSound(&mousemovemusic);
				break;
			case 2: // 退出
				SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
				break;
			}
		}
		else if (game_state == GAME_UPGRADE)
		{
			switch (index)
			{
			case 0: // 下一关
				clear();
				game_state = GAME_RUN;
				BeginPass(pass + 1);
				break;
			case 1: // 返回
				clear();
				game_state = GAME_START;
				gameMenu->LoadGameMenu(GAME_START);
				gameMenu->SetClickSound(&mousedownmusic);
				gameMenu->SetMoveSound(&mousemovemusic);
				break;
			case 2: // 退出
				SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
				break;
			}
		}
		else if (game_state == GAME_WIN)
		{
			switch (index)
			{
			case 0: // 重新开始
				clear();
				game_state = GAME_RUN;
				BeginPass(1);
				break;
			case 1: // 返回
				clear();
				game_state = GAME_START;
				gameMenu->LoadGameMenu(GAME_START);
				gameMenu->SetClickSound(&mousedownmusic);
				gameMenu->SetMoveSound(&mousemovemusic);
				break;
			case 2: // 退出
				SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
				break;
			}
		}
		else if (game_state == GAME_OVER)
		{
			switch (index)
			{
			case 0: // 重新开始本关
				clear();
				game_state = GAME_RUN;
				BeginPass(pass);
				break;
			case 1: // 返回
				clear();
				game_state = GAME_START;
				gameMenu->LoadGameMenu(GAME_START);
				gameMenu->SetClickSound(&mousedownmusic);
				gameMenu->SetMoveSound(&mousemovemusic);
				break;
			case 2: // 退出
				SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
				break;
			}
		}
	}
	return game_state;
}

void MainEngine::BeginPass(int p)
{
	pass = p;
	npc_num = 10;
	gameMenu->LoadGameMenu(GAME_RUN);
	gameMenu->SetClickSound(&mousedownmusic);
	gameMenu->SetMoveSound(&mousemovemusic);
	char mapname[32];
	sprintf(mapname, ".\\res\\map_pass%d.txt", pass);
	LoadMap(mapname);
	LoadNpc(npc_num);
	LoadPlayer();
}