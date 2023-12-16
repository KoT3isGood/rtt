#include "GameLoader.h"


GameLoader::~GameLoader()
{
	// Prevents memory leaks
	KillDll(); 
}

void GameLoader::UpdateDll(std::string dllName)
{
	// Kills current DLL to prevent memory leak
	// Sets loading status to false because it doesn't get reset when beign updated using LoadingStatus = (currentDll != nullptr);
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
void GameLoader::KillDll()
{
	if (LoadingStatus) {
		FreeLibrary(currentDll);
		return;
	}
}