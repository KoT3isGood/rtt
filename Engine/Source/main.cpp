#include "EngineMacros.h"

#include "Runtime/Engine/GameLoader/CurrentGame.h"
#include "Runtime/Engine/Rendering/WindowGenerator.h"
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    CurrentGame::setCurrentGame("Sandbox.dll");
    GameWindow();
    return 0;
}