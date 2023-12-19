#pragma once
#include "Runtime/Engine/Rendering/Include/glad/glad.h"
#include "Runtime/Engine/Rendering/Include/GLFW/glfw3.h"
#include <vector>


class Buffer {
public:
    unsigned int buffer;
    int b;
    Buffer() = default;
    Buffer(int binding);

    void SetData(int size, std::vector<int>* data);
    void SetData(int size, std::vector<float>* data);
};