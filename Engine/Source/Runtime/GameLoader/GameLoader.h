#include "EngineMacros.h"

class GameLoader {
public:
	GameLoader() = default;
	void UpdateDll(std::string dllName);
	void TickWorld();
private:
	HMODULE currentDll;
	bool LoadingStatus = false;
};