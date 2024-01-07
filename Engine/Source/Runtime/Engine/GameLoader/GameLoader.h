#pragma once
#include "EngineMacros.h"
#include "Runnable/World/World.h"
#include <filesystem>

class GameLoader {
public:
	GameLoader() = default;
	~GameLoader();
	std::string currentGame;
	std::string currentGamePath;

	// Sets current DLL
	void UpdateDll(std::string dllName);
	// Kills current DLL
	void KillDll();

	// Runs function by name
	void RunVoidFunction(std::string name);
	// Returns world
	World* GetWorld();
	// Creates world copy
	// For debugging;
	World* GetWorldCopy();
	void LoadWorldFromName(std::string path);
private:
	HMODULE currentDll;
	bool LoadingStatus = false;
};