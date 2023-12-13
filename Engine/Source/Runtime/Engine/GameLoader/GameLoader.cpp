#include "GameLoader.h"



void GameLoader::UpdateDll(std::string dllName)
{
	
	this->KillDll();
	this->LoadingStatus = false;
	currentDll = LoadLibraryA(dllName.c_str());
	LoadingStatus = (currentDll != nullptr);
	if (LoadingStatus) {
		PRINTADVANCED("DLL " + dllName + " was loaded successfully", info);
		return;
	}
	PRINTADVANCED("Failed to load DLL " + dllName, error);
}

void GameLoader::TickWorld()
{
	if (!LoadingStatus) {
		return;
	}
	// since i can only interact with functions i will use them, and so i will create world actors pointer
	using UpdateWorldPtr = void (*)();
	UpdateWorldPtr updateWorld = (UpdateWorldPtr)GetProcAddress(currentDll, "UpdateWorld");

	if (updateWorld == nullptr) {
		
		PRINTADVANCED("Function was not found", error);
		return;
	}
	
	updateWorld();
	PRINTADVANCED("Function activated", info);
}
void GameLoader::KillDll()
{
	
	if (LoadingStatus) {
		FreeLibrary(currentDll);
		return;
	}
}