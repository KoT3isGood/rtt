#pragma once
#include "Runtime/Engine/Rendering/Include/glad/glad.h"
#include "Runtime/Engine/Rendering/Include/GLFW/glfw3.h"
#include "EngineMacros.h"

class RenderTexture {
public:
    ivec2 resolution;
    int id;
    unsigned int texture;



    RenderTexture() = default;
    RenderTexture(ivec2 res, int ID);
    void BindTextureAndUpdateRes(ivec2 res);
};
