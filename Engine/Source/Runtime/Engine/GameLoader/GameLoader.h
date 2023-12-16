#pragma once
#include "EngineMacros.h"

class GameLoader {
public:
	GameLoader() = default;
	~GameLoader();
	std::string currentGame;

	// Sets current DLL
	void UpdateDll(std::string dllName);
	// Kills current DLL
	void KillDll();

	// Runs function by name
	void RunVoidFunction(std::string name);
private:
	HMODULE currentDll;
	bool LoadingStatus = false;
};