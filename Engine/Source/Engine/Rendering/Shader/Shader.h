#pragma once
#include "Runtime/Engine/Rendering/Include/glad/glad.h"
#include "Runtime/Engine/Rendering/Include/GLFW/glfw3.h"
#include "EngineMacros.h"

#include <string>
#include <fstream>
#include <sstream>

class Shader
{
public:
    unsigned int ID;
    Shader() = default;
    Shader(const char* computePath);
    void use();
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, vec3 value) const;
    void setVec2(const std::string& name, vec2 value) const;
    void UpdateShader();


private:
    char* cp;
    void checkCompileErrors(unsigned int shader, std::string type);
};
