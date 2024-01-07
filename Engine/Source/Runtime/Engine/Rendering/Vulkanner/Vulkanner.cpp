#include "Vulkanner.h"
#include "Runtime/Engine/GameLoader/CurrentGame.h"

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
	pathTracer = Shader("pathTracer.comp");
	albedoOutput = RenderTexture(*resolution, 0);
	triangle = Buffer(0);
    sphere = Buffer(3);
    boundingBox = Buffer(2);







    // Background Drawing








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

    int triAmount = 0;
    int bbAmount = 0;
    int lightsAmount = 0;


    
    GameLoader* currentGame = CurrentGame::getCurrentGame();
    if (currentGame->currentGame != "") {
        Actor* currentActor = CurrentGame::getCurrentGame()->GetWorld()->currentPlayerController.ownedActor;
        if (currentActor == nullptr) {
        } else {

            CameraComponent* currentCamera = currentActor->currentCamera;
            if (currentCamera == nullptr) {
            } else 
            {
                vec3 vertex = currentActor->currentCamera->position;
                vertex = vec3(vertex.x, vertex.z, vertex.y);
                vertex *= currentActor->size;
                mat3x3 ActorRotation = rotationToMat3x3(currentActor->rotation);
                mat3x3 CameraRotation = rotationToMat3x3(currentActor->currentCamera->rotation);
                vertex = ActorRotation * vertex;
                vertex += currentActor->position;

                mat3 cameraMatrix = ActorRotation * CameraRotation;

                pathTracer.setVec3("cameraPos", vec3(vertex));
                pathTracer.setVec3("cameraRotationM1", vec3(cameraMatrix[0]));
                pathTracer.setVec3("cameraRotationM2", vec3(cameraMatrix[1]));
                pathTracer.setVec3("cameraRotationM3", vec3(cameraMatrix[2]));
                
            }
        }





        std::vector<float>* geometry = currentGame->GetWorld()->GetWorldGeometry();
        std::vector<float>* bb = currentGame->GetWorld()->GetBoundingBoxes();
        std::vector<float>* lights = currentGame->GetWorld()->GetWorldLights();
        triAmount = geometry->size();
        triangle.SetData(triAmount, geometry);
        bbAmount = bb->size();
        boundingBox.SetData(bbAmount, bb);
        lightsAmount = lights->size();
        sphere.SetData(lightsAmount, lights);

    }
    else {
        std::vector<float>triangles = {};
        triangle.SetData(0, &triangles);
        boundingBox.SetData(0, &triangles);
        sphere.SetData(0, &triangles);
    }

    
	

	albedoOutput.BindTextureAndUpdateRes(*resolution);
	pathTracer.use();
    pathTracer.setVec3("cameraPos", vec3(0.0, 0.0, 0));
    pathTracer.setVec3("cameraRotationM1", vec3(0.0, 0.0, 0.0));
    pathTracer.setVec3("cameraRotationM2", vec3(0.0, 0.0, 0.0));
    pathTracer.setBool("isOrto", false);
    pathTracer.setFloat("orthoSize", 1.0);

    if (currentGame->currentGame != "") {
        Actor* currentActor = CurrentGame::getCurrentGame()->GetWorld()->currentPlayerController.ownedActor;
        if (currentActor == nullptr) {
        }
        else {

            CameraComponent* currentCamera = currentActor->currentCamera;
            if (currentCamera == nullptr) {
            }
            else
            {
                mat3x3 ActorRotation = rotationToMat3x3(vec3(currentActor->rotation.x, currentActor->rotation.y, currentActor->rotation.z));
                mat3x3 CameraRotation = rotationToMat3x3(currentActor->currentCamera->rotation);

                vec3 vertex = currentActor->currentCamera->position;
                vertex = vec3(vertex.x, vertex.z, vertex.y);
                vertex *= currentActor->size;
                vertex = ActorRotation * vertex;
                vertex += currentActor->position;

                pathTracer.setVec3("cameraPos", vec3(vertex));
                pathTracer.setVec3("cameraRotationM1", vec3(currentActor->currentCamera->rotation));
                pathTracer.setVec3("cameraRotationM2", vec3(currentActor->rotation));
                pathTracer.setBool("isOrto", currentActor->currentCamera->isOrtoGraphic);
                pathTracer.setFloat("orthoSize", currentActor->currentCamera->orthoSize);
            }
        }
    }



	pathTracer.setVec2("resolution", vec2(resolution->x, resolution->y));
    pathTracer.setInt("amountOfTriangles", int(triAmount*0.0625));
    pathTracer.setInt("amountOfBoundingBoxes", int(bbAmount*0.125));
    pathTracer.setInt("amountOfLights", int(lightsAmount*0.125));
    
    //pathTracer.setBool("isOrto", false);

    

	glDispatchCompute(int(resolution->x*0.125+1), int(resolution->y*0.125+1), 1);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);















    glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "textIn"), triangle.b);
    glUniform2f(glGetUniformLocation(shaderProgram, "resolution"), resolution->x, resolution->y);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    
}
