#include "main.h"
#include "ZombieGame.h"

#include <windows.h>

ZombieGame* g_pZombieGame = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, int nShowCmd)
{
	g_pZombieGame = new ZombieGame();

	// try to initialize the game
	if (!g_pZombieGame->Init(400, 400))
		return 0;

	g_pZombieGame->Go();

	// reclaim the memory
	delete g_pZombieGame;

	return 0;
}
