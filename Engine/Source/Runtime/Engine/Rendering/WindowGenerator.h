#pragma once
#include "EngineMacros.h"

#define GLFW_INCLUDE_NONE
#include "Include/GLFW/glfw3.h"
#include "Include/glad/glad.h"

#include "Vulkanner/Vulkanner.h"

#include "..\..\Engine\Source\Editor\Interface\EditorInterface.h"


class GameWindow {
public:
	GameWindow();
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	ivec2 window_size = ivec2(1280,720);
private:
	EditorInterface editor;
	Vulkanner vulkannerRendering;
};