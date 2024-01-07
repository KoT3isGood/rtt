#include "WindowGenerator.h"

//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    glViewport(0, 0, width, height);
//}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    //setWindowSize(width, height);
//#ifdef NOGUI
    glViewport(0, 0, width, height);
//#endif
}
void GameWindow::setWindowSize(int width, int height)
{
    window_size.x = width;
    window_size.y = height;
}
;
WNDPROC original_proc;


GameWindow::GameWindow()
{
    PRINTADVANCED("Creating Rendering", glsl);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(window_size.x, window_size.y, "Retto", NULL, NULL);
    if (window == NULL)
    {
        PRINTADVANCED("Failed to create window", glslerror);
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);



    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        PRINTADVANCED("Failed to initialize GLAD", glslerror);
        return;
    }




   
    glViewport(0, 0, window_size.x, window_size.y);
    

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    editor.currentWindowSize = &window_size;
    editor.currentWindow = window;
   
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window,true);
    ImGui_ImplOpenGL3_Init("#version 330");

   
    vulkannerRendering = Vulkanner();
    vulkannerRendering.Init();
    int prevf = 0;
    int curf = 0;
    float fpsCounterDelta = 0.0;

    while (!glfwWindowShouldClose(window) && editor.shouldAppBeOpened)
    {

        



        // 1. calculate delta time
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        curf = glfwGetTime() * 10000;
        curf = curf % 1000;
        if (curf < prevf) {
            fpsCounterDelta = deltaTime;
        }
        prevf = curf;

        // 2. execute code from dll
        World* currentWorld = CurrentGame::getCurrentGame()->GetWorld();

        if (currentWorld != nullptr) {
            currentWorld->UpdateWorld(deltaTime);
            CurrentGame::getCurrentGame()->GetWorld()->PrecalculateTriangles();
            
        }
       


        // 3. update physics











        //glfwGetWindowSize(window, &window_size.x, &window_size.y);
        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        
        #ifndef NOGUI
        window_size = editor.viewportSizeMirror;
        #else 
        glfwGetWindowSize(window, &window_size.x, &window_size.y);
        #endif
        vulkannerRendering.Update(&window_size, deltaTime);

       
        

        

        

        editor.fpsCounterDelta = fpsCounterDelta;
        editor.viewportTexture = &vulkannerRendering.albedoOutput;
        editor.CreateInterface();
        

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context); 
        }
        glfwPollEvents();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);

    glfwTerminate();
}

