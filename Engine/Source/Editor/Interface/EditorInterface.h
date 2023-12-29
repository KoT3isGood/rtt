#pragma once

#include "..\..\Libraries\ImGui\imgui.h"
#include "..\..\Libraries\ImGui\imgui_impl_glfw.h"
#include "..\..\Libraries\ImGui\imgui_impl_opengl3.h"
#include "Editor/ImGLM/Convertor.h"
//#include <Runtime/Engine/Rendering/Include/GLFW/glfw3.h>
#include "Runtime/Engine/GameLoader/CurrentGame.h"

//#include "Engine/Rendering/Buffer/Buffer.h"
//#include "Engine/Rendering/Shader/Shader.h"
#include "Engine/Rendering/Texture/Texture.h"
#include "Runtime/Game/WhatTheHeader/Reflector.h"


class EditorInterface {
public:
	

	EditorInterface() = default;
	void CreateInterface();
	ivec2* currentWindowSize;
	GLFWwindow* currentWindow;

	ImVec2 prevMouse = ImVec2(0.0,0.0);
	ImVec2 viewportSize;
	ivec2 viewportSizeMirror = ivec2(1280,720);

	RenderTexture* viewportTexture;

	bool shouldGameLoaderBeOpened = true;
	bool shouldAppBeOpened = true;
	bool isRunning = false;
	World worldEditorCopy;
	std::vector<Actor*> actorsEditorCopy;

	float fpsCounterDelta = 1.0;
private:
	void CreateDockSpace();
	void CreateGameLoader();
	void CreateViewport();
	void CreateActorBrowser();
	void CreateActorProperties();
	void GenerateRegister(std::string variableType, std::string variableNameStr, void* variable);
	int selectedActor = -1;
};