#include "EngineMacros.h"

#include "Runtime/GameLoader/GameLoader.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    GameLoader game = GameLoader();
    game.UpdateDll("Sandbox.dll");
    return 0;
}