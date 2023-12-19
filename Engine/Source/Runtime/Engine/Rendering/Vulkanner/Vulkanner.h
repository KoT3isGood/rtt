#pragma once
#include "EngineMacros.h"

#define GLFW_INCLUDE_NONE
#include "..\Include/GLFW/glfw3.h"
#include "..\Include/glad/glad.h"

#include "Engine/Rendering/Buffer/Buffer.h"
#include "Engine/Rendering/Shader/Shader.h"
#include "Engine/Rendering/Texture/Texture.h"

class Vulkanner {
public:
	Vulkanner();

	void Init();
	void Update(ivec2 *resolutionPtr);

	RenderTexture albedoOutput;
	ivec2* resolution;

	// Textures Shaders Buffers etc
	Shader pathTracer;
	Buffer triangle;
private:
	unsigned int shaderProgram;
	unsigned int VAO;
};