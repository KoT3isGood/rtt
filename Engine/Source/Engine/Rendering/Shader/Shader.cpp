#include "Shader.h"
Shader::Shader(const char* computePath)
{
    cp = (char*)computePath;
    // Get shader code
    std::string computeCode;
    std::ifstream cShaderFile;
    // Try if everything is ok
    cShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        cShaderFile.open(computePath);
        std::stringstream cShaderStream;
        cShaderStream << cShaderFile.rdbuf();
        cShaderFile.close();
        computeCode = cShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        PRINTADVANCED("Shader file was not successfully read ", glslerror);
        PRINTADVANCED(std::string(e.what()), glslerror);
        return;
    }
    const char* cShaderCode = computeCode.c_str();
    // Compile shaders
    unsigned int compute;
    compute = glCreateShader(GL_COMPUTE_SHADER);

    glShaderSource(compute, 1, &cShaderCode, NULL);
    glCompileShader(compute);
    checkCompileErrors(compute, "COMPUTE");
    // Create Program
    ID = glCreateProgram();
    glAttachShader(ID, compute);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // Delete Shader
    glDeleteShader(compute);
}
// glUseProgram
void Shader::use()
{
    glUseProgram(ID);
}
// Set data in shader
void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setVec3(const std::string& name, vec3 value) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}
void Shader::setVec2(const std::string& name, vec2 value) const
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), value.x, value.y);
}
void Shader::UpdateShader()
{
    // Get shader code
    std::string computeCode;
    std::ifstream cShaderFile;
    // Try if everything is ok
    cShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        cShaderFile.open(cp);
        std::stringstream cShaderStream;
        cShaderStream << cShaderFile.rdbuf();
        cShaderFile.close();
        computeCode = cShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        PRINTADVANCED("Shader file was not successfully read ", glslerror);
        PRINTADVANCED(std::string(e.what()), glslerror);
        return;
    }
    const char* cShaderCode = computeCode.c_str();
    // Compile shaders
    unsigned int compute;
    compute = glCreateShader(GL_COMPUTE_SHADER);

    glShaderSource(compute, 1, &cShaderCode, NULL);
    glCompileShader(compute);
    checkCompileErrors(compute, "COMPUTE");
    // Create Program
    ID = glCreateProgram();
    glAttachShader(ID, compute);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // Delete Shader
    glDeleteShader(compute);
}
void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            PRINTADVANCED("Shader was not successfully compiled", glslerror);
            PRINTADVANCED(std::string(infoLog), glslerror);
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            PRINTADVANCED("Program was not successfully linked", glslerror);
            PRINTADVANCED(std::string(infoLog), glslerror);
        }
    }
}