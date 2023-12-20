#include "Vulkanner.h"

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   ourColor = aColor;\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"uniform sampler2D textIn;\n"
"void main()\n"
"{\n"
    "vec2 uv = vec2(ourColor.y,1-ourColor.x);\n"
"   FragColor = vec4(texture(textIn,uv).xyz, 1.0f);\n"
"}\n\0";

// set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
float vertices[] = {
    -1.0f, 1.0f, 0.0f, 0.0f,0.0f,0.0f,

     -1.0f, -1.0f, 0.0f, 1.0f,0.0f,0.0f,

     1.0f,  1.0f, 0.0f, 0.0f,1.0f,0.0f,

     -1.0f, -1.0f, 0.0f, 1.0f,0.0f,0.0f,

     1.0f,  1.0f, 0.0f, 0.0f,1.0f,0.0f,

      1.0f, -1.0f, 0.0f, 1.0f,1.0f,0.0f,
};

Vulkanner::Vulkanner()
{

    

}

void Vulkanner::Init()
{
	pathTracer = Shader("Source/Runtime/Engine/Rendering/Vulkanner/Shaders/pathTracer.comp");
	albedoOutput = RenderTexture(*resolution, 0);
	triangle = Buffer(0);

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        PRINTADVANCED("Vertex compilation failed", glslerror);
        PRINTADVANCED(infoLog, glslerror);
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        PRINTADVANCED("Fragment compilation failed", glslerror);
        PRINTADVANCED(infoLog, glslerror);
    }
    // link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        PRINTADVANCED("Linking failed", glslerror);
        PRINTADVANCED(infoLog, glslerror);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    unsigned int VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Vulkanner::Update(ivec2 *resolutionPtr,float deltaTime)
{

	resolution = resolutionPtr;
	
	std::vector<float> triangles = {
	1,0,0,1,
	0,1,0,1,
	0,0,1,1,
    1,1,1,1,
	};
	triangle.SetData(12, &triangles);

	albedoOutput.BindTextureAndUpdateRes(*resolution);
	pathTracer.use();
	pathTracer.setVec2("resolution", vec2(resolution->x, resolution->y));
    pathTracer.setInt("amountOfTriangles", 1);

    int w, h;
    int miplevel = 0;
    glBindTexture(GL_TEXTURE_2D, albedoOutput.texture);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &w);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_HEIGHT, &h);
    
    pathTracer.setBool("isOrto", false);

    pathTracer.setVec3("cameraPos", vec3(-2, 0, 0));
    pathTracer.setVec3("cameraRotation", vec3(0.0, 0.0, 0.0));

    test += deltaTime;
	glDispatchCompute(int(resolution->x/8+1), int(resolution->y/8+1), 1);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
	

    //glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "textIn"), triangle.b);
    glUniform2f(glGetUniformLocation(shaderProgram, "resolution"), resolution->x, resolution->y);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    
}
