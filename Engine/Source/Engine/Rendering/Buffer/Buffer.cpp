#include "Buffer.h"

// Sets data of buffer
// Some bindings are reserved
// 0 - Triangles (4x4 matrix), 64 bytes in total
// Why? it includes triangle and it's vertices and uv's

Buffer::Buffer(int binding)
{
    b = binding;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, b, buffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

// Sets data of buffer
void Buffer::SetData(int size, std::vector<int>* data)
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, size * 4, data->data(), GL_DYNAMIC_READ);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}
// Sets data of buffer
void Buffer::SetData(int size, std::vector<float>* data)
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, size * 4, data->data(), GL_DYNAMIC_READ);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}