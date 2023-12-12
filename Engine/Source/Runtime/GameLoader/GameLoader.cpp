#include "GameLoader.h"

void GameLoader::UpdateDll(std::string dllName)
{
	currentDll = LoadLibraryA("Sandbox.dll");
	LoadingStatus = currentDll != nullptr;
	if (LoadingStatus) {
		FreeLibrary(currentDll);
		return;
	}
	OutputDebugStringA("Hello gigga niga");
}

void GameLoader::TickWorld()
{
}
