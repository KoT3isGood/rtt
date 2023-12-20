#pragma once
#include "EngineMacros.h"
#include "Runnable/World/World.h"

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

	// Returns world
	World* GetWorld();
private:
	HMODULE currentDll;
	bool LoadingStatus = false;
};