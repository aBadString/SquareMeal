#include "MainEngine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	LPCTSTR WinTitle = L"Square Meal";
	MainEngine* test = new MainEngine(hInstance, WIN_CLASS, WinTitle, NULL, NULL, 1024, 768);
	T_Engine::pEngine = test;
	test->SetFrame(60);
	test->StartEngine();

	return 0;
}

// TODO: 加油，以后把这个游戏写完整！！