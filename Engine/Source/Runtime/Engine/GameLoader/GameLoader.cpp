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
	PRINT(std::to_string(LoadingStatus));
	if (LoadingStatus) {
		this->currentGame = dllName;
		this->currentGamePath = std::filesystem::path(currentGame).parent_path().string();
		if (!std::filesystem::exists(this->currentGamePath + "/content")) {
			std::filesystem::create_directory(this->currentGamePath + "/content");
		}
		std::filesystem::current_path(currentGamePath);
		PRINT("DLL Was loaded successfuly");
		return;
	}
}

void GameLoader::RunVoidFunction(std::string name)
{
	if (!LoadingStatus) {
		PRINTADVANCED("DLL was not found",error);
		return;
	}
	// Creates new void function
	// Gets address of the function
	using FunctionCaller = void (*)();
	FunctionCaller functionCaller = (FunctionCaller)GetProcAddress(currentDll, name.c_str());
	if (functionCaller == nullptr) {
		PRINTADVANCED("Function was not found", error);
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
World* GameLoader::GetWorldCopy()
{
	if (!LoadingStatus) {
		return nullptr;
	}
	// Creates new void function
	// Gets address of the function
	using FunctionCaller = World * (*)();
	FunctionCaller functionCaller = (FunctionCaller)GetProcAddress(currentDll, "GetWorldCopy");
	if (functionCaller == nullptr) {
		PRINTADVANCED("Failed to find world copy, please make sure to...", error);
		return nullptr;
	}

	// Calls function
	return functionCaller();
}

void GameLoader::LoadWorldFromName(std::string path)
{
	if (!LoadingStatus) {
		return;
	}
	// Creates new void function
	// Gets address of the function
	using FunctionCaller = Actor * (*)(std::string);
	FunctionCaller functionCaller = (FunctionCaller)GetProcAddress(currentDll, "LoadWorldFromName");
	if (functionCaller == nullptr) {
		PRINTADVANCED("Failed to find world copy, please make sure to...", error);
		return;
	}

	// Calls function
	functionCaller(path);
}


void GameLoader::KillDll()
{
	if (LoadingStatus) {
		this->LoadingStatus = false;
		this->currentGame = "";
		FreeLibrary(currentDll);
		return;
	}
}