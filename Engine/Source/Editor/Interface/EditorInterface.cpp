#include "EditorInterface.h"


void EditorInterface::CreateInterface()
{
#ifndef NOGUI
    //preset
    CreateDockSpace();
    CreateGameLoader();
    //Should be disabled if no DLL
    ImGui::BeginDisabled(CurrentGame::getCurrentGame()->currentGame=="");
    CreateViewport();
    CreateActorProperties();
    ImGui::EndDisabled();
#endif
}

void EditorInterface::CreateDockSpace()
{
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar;
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
    ImGui::Begin("DockSpace", &shouldAppBeOpened, window_flags);
    
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
        if(ImGui::BeginMenu("File")) {
            ImGui::MenuItem("New", "Ctrl+N");
            if (ImGui::MenuItem("Open", "Ctrl+O")) {
                shouldGameLoaderBeOpened = true;
            };
            ImGui::MenuItem("Save", "Ctrl+S");
            ImGui::MenuItem("Save as","Ctrl+Shift+S");
            ImGui::Separator();
            if (ImGui::MenuItem("Exit", "Alt+F4")) { shouldAppBeOpened = false; };
            ImGui::EndMenu();
       }
           
        
       
        

        ImGui::EndMenuBar();
    }
   
   
    ImGui::End();
}

void EditorInterface::CreateGameLoader()
{
    if (shouldGameLoaderBeOpened) {
        ImGui::Begin("Game Loading Tool", &shouldGameLoaderBeOpened, ImGuiWindowFlags_NoTitleBar);
        
        if (ImGui::Button("Load Sandbox.dll")) {
            shouldGameLoaderBeOpened = false;
            CurrentGame::setCurrentGame("Sandbox.dll");
        }
        ImGui::End();
    }
}

void EditorInterface::CreateViewport()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding,ImVec2(0,0));
    ImGui::Begin("Viewport",(bool*)0,ImGuiWindowFlags_NoCollapse);
    ImGui::Text("test");
    viewportSize = ImGui::GetContentRegionAvail();
    viewportSizeMirror = ivec2(viewportSize.x, viewportSize.y);
    ImGui::Image((void*)viewportTexture->texture, viewportSize,ImVec2(0,1),ImVec2(1,0));
    ImGui::Text("test2");
    ImGui::End();
    ImGui::PopStyleVar();
    
}

void EditorInterface::CreateActorBrowser()
{
    
}

void EditorInterface::CreateActorProperties()
{
    ImGui::Begin("Actor Properties");
    ImGui::End();
}
