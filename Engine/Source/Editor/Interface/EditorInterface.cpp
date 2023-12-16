#include "EditorInterface.h"


void EditorInterface::CreateInterface()
{
    //preset
    CreateDockSpace();
    CreateGameLoader();
    //Should be disabled if no DLL
    ImGui::BeginDisabled(CurrentGame::getCurrentGame()->currentGame=="");
    CreateViewport();
    ImGui::EndDisabled();
}

void EditorInterface::CreateDockSpace()
{
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    bool p_open = true;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;
    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace", &p_open, window_flags);
    
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);
    
    // Submit the DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

       
    }
    bool Menubar = ImGui::BeginMenuBar();
    if (Menubar)
    {
        ImGui::Text("123");
        //if (ImGui::IsItemHovered()) {


        //    int windowPosX = 0;
        //    int windowPosY = 0;
        //    glfwGetWindowPos(currentWindow, &windowPosX, &windowPosY);

        //    int windowSizeX = 0;
        //    int windowSizeY = 0;
        //    glfwGetWindowSize(currentWindow, &windowSizeX, &windowSizeY);
        //    ImVec2 currentPos = ImGui::GetMouseDragDelta();
        //    ImVec2 mousePos = ImGui::GetMousePos();
        //    if (mousePos.x > windowPosX && mousePos.x < windowSizeX + windowPosX && // x
        //        mousePos.y > windowPosY && mousePos.y < windowSizeY + windowPosY // y
        //     
        //        ) {
        //        PRINT(std::to_string(ImGui::GetMouseDragDelta().x));
        //        PRINT(std::to_string(ImGui::GetMouseDragDelta().y));

        //        
        //       
        //        if (currentPos.x != 0 && currentPos.y != 0) {
        //            glfwSetWindowPos(currentWindow, windowPosX + (currentPos.x - prevMouse.x) + 6, windowPosY + (currentPos.y - prevMouse.y) + 30);
        //            prevMouse = currentPos;
        //        }
        //        else {
        //            prevMouse = ImVec2(0.0,0.0);
        //        }
        //        
        //    };
        //}
           
        
       
        

        ImGui::EndMenuBar();
    }
   
   
    ImGui::End();
}

void EditorInterface::CreateGameLoader()
{

    ImGui::Begin("Game Loading Tool");

    if (ImGui::Button("Load Sandbox.dll")) {
        CurrentGame::setCurrentGame("Sandbox.dll");
    }







    ImGui::End();
}

void EditorInterface::CreateViewport()
{
    ImGui::Begin("Viewport");
    
    if (ImGui::Button("Update world")) {
        CurrentGame::getCurrentGame()->RunVoidFunction("UpdateWorld");
    };
    ImGui::End();
}

void EditorInterface::CreateActorBrowser()
{
}

void EditorInterface::CreateActorProperties()
{
}