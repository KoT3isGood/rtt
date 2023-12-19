#pragma once
#include "EngineMacros.h"

#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_NATIVE_INCLUDE_NONE
#include "Include/GLFW/glfw3.h"
#include "Include/GLFW/glfw3native.h"
#include "Include/glad/glad.h"

#include "Vulkanner/Vulkanner.h"

#include "..\..\Engine\Source\Editor\Interface\EditorInterface.h"

#include "Engine/Rendering/Buffer/Buffer.h"
#include "Engine/Rendering/Shader/Shader.h"
#include "Engine/Rendering/Texture/Texture.h"


class GameWindow {
public:
	GameWindow();
	ivec2 window_size = ivec2(1280,720);
private:
	void setWindowSize(int width, int height);
	EditorInterface editor;
	Vulkanner vulkannerRendering;
};