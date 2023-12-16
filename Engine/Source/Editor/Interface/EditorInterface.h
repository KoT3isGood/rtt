#pragma once

#include "..\..\Libraries\ImGui\imgui.h"
#include "..\..\Libraries\ImGui\imgui_impl_glfw.h"
#include "..\..\Libraries\ImGui\imgui_impl_opengl3.h"
#include <Runtime/Engine/Rendering/Include/GLFW/glfw3.h>
#include "Runtime/Engine/GameLoader/CurrentGame.h"
#include <shobjidl.h> 

class EditorInterface {
public:
	EditorInterface() = default;
	void CreateInterface();
	ivec2* currentWindowSize;
	GLFWwindow* currentWindow;

	ImVec2 prevMouse = ImVec2(0.0,0.0);
private:
	void CreateDockSpace();
	void CreateGameLoader();
	void CreateViewport();
	void CreateActorBrowser();
	void CreateActorProperties();

};