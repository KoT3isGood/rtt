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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(window_size.x, window_size.y, "Retto", NULL, NULL);
    #ifndef NOGUI
    #endif
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




    vulkannerRendering = Vulkanner(&window_size);
    glViewport(0, 0, window_size.x, window_size.y);
    

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
#ifndef NOGUI
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

   
#endif

    vulkannerRendering.Init();



    while (!glfwWindowShouldClose(window))
    {
        glfwGetWindowSize(window, &window_size.x, &window_size.y);

        #ifndef NOGUI
        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
        #endif

        vulkannerRendering.Update();
        glClear(GL_COLOR_BUFFER_BIT);

        

        

        

        #ifndef NOGUI
      
        editor.CreateInterface();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
       
        #endif

        glfwSwapBuffers(window);
        #ifndef NOGUI
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
        #endif
        glfwPollEvents();
    }
    #ifndef NOGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    #endif
    glfwDestroyWindow(window);

    glfwTerminate();
}

