#pragma once
#include "EngineMacros.h"

#define GLFW_INCLUDE_NONE
#include "..\Include/GLFW/glfw3.h"
#include "..\Include/glad/glad.h"

class Vulkanner {
public:
	Vulkanner() = default;
	Vulkanner(ivec2* resolutionPtr);

	void Init();
	void Update();
private:
	ivec2* resolution;
	// Textures Shaders Buffers etc
};