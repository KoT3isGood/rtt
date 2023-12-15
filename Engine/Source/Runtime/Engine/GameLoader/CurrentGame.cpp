#include "CurrentGame.h"

GameLoader currentGameDll = GameLoader();

GameLoader* CurrentGame::getCurrentGame()
{
	return &currentGameDll;
}

void CurrentGame::setCurrentGame(std::string name)
{
	currentGameDll.UpdateDll(name);
}
void CurrentGame::killCurrentGame()
{
	currentGameDll.KillDll();
}
