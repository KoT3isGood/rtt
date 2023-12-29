#pragma once
#include "GameLoader.h"


namespace CurrentGame {
	GameLoader* getCurrentGame();
	void setCurrentGame(std::string name);
	void killCurrentGame();
};