#pragma once
#include "EngineMacros.h"

class GameLoader {
public:
	GameLoader() = default;
	~GameLoader();
	std::string currentGame;

	void UpdateDll(std::string dllName);
	void KillDll();

	void RunVoidFunction(std::string name);
private:
	HMODULE currentDll;
	bool LoadingStatus = false;
};