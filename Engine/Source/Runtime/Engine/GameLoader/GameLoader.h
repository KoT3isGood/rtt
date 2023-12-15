#pragma once
#include "EngineMacros.h"

class GameLoader {
public:
	GameLoader() = default;
	
	std::string currentGame;

	void UpdateDll(std::string dllName);
	void KillDll();

	void TickWorld();
private:
	HMODULE currentDll;
	bool LoadingStatus = false;
};