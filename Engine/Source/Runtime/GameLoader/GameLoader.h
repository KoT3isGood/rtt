#include "EngineMacros.h"
class GameLoader {
public:
	void UpdateDll(std::string dllName);
	void TickWorld();
private:
	HMODULE currentDll;

};