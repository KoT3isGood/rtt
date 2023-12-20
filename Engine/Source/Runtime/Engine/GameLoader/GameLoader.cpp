#include "GameLoader.h"


GameLoader::~GameLoader()
{
	// Prevents memory leaks
	KillDll(); 
}

void GameLoader::UpdateDll(std::string dllName)
{
	// Kills current DLL to prevent memory leak
	this->KillDll();
	this->LoadingStatus = false;

	// Loads DLL
	currentDll = LoadLibraryA(dllName.c_str());

	// Checks if it was successful
	LoadingStatus = (currentDll != nullptr);
	if (LoadingStatus) {
		this->currentGame = dllName;
		return;
	}
}

void GameLoader::RunVoidFunction(std::string name)
{
	if (!LoadingStatus) {
		return;
	}
	// Creates new void function
	// Gets address of the function
	using FunctionCaller = void (*)();
	FunctionCaller functionCaller = (FunctionCaller)GetProcAddress(currentDll, name.c_str());
	if (functionCaller == nullptr) {
		return;
	}

	// Calls function
	functionCaller();
}
World* GameLoader::GetWorld()
{
	if (!LoadingStatus) {
		return nullptr;
	}
	// Creates new void function
	// Gets address of the function
	using FunctionCaller = World* (*)();
	FunctionCaller functionCaller = (FunctionCaller)GetProcAddress(currentDll, "GetWorld");
	if (functionCaller == nullptr) {
		PRINTADVANCED("Failed to find world, please make sure you have CurrentProperties.h in your game", error);
		return nullptr;
	}

	// Calls function
	return functionCaller();
}
void GameLoader::KillDll()
{
	if (LoadingStatus) {
		FreeLibrary(currentDll);
		return;
	}
}