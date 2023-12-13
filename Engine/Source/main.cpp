#include "EngineMacros.h"

#include "Runtime/Engine/GameLoader/GameLoader.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    GameLoader game = GameLoader();
    game.UpdateDll("Sandbox.dll");
    game.TickWorld();
    game.KillDll();
    return 0;
}