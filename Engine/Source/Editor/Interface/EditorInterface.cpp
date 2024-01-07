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
    CreateActorBrowser();
    CreateActorProperties();
    ImGui::EndDisabled();
#endif
}
void EditorInterface::LoadCustomInterface()
{

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
        if (CurrentGame::getCurrentGame()->currentGame != "") {
            ImGui::BeginDisabled(CurrentGame::getCurrentGame()->GetWorld()->isTickingEnabled);
        }
        
        if(ImGui::BeginMenu("File")) {

            ImGui::MenuItem("New", "Ctrl+N");
           
            /*if (!CurrentGame::getCurrentGame()->GetWorld()->isTickingEnabled) {

            }*/
            if (ImGui::MenuItem("Open", "Ctrl+Shift+O")) {
                CurrentGame::getCurrentGame()->LoadWorldFromName("");
                shouldGameLoaderBeOpened = true;
            };
            ImGui::MenuItem("Save", "Ctrl+S");
            if (ImGui::MenuItem("Save as", "Ctrl+Shift+S")) {
                CurrentGame::getCurrentGame()->GetWorld()->SerializeWorld("worlds", "testWorld");
            };
            ImGui::Separator();
            if (ImGui::MenuItem("Exit", "Alt+F4")) { shouldAppBeOpened = false; };
            
            ImGui::EndMenu();
            
       }
        if (CurrentGame::getCurrentGame()->currentGame != "") {
        ImGui::EndDisabled();
        }
        
        

        if (CurrentGame::getCurrentGame()->currentGame != "") {

            if (!CurrentGame::getCurrentGame()->GetWorld()->isTickingEnabled) {
                if (ImGui::Button("Play")) {
                    worldEditorCopy = *CurrentGame::getCurrentGame()->GetWorldCopy();
                    CurrentGame::getCurrentGame()->GetWorld()->isTickingEnabled = true;
                    CurrentGame::getCurrentGame()->GetWorld()->currentPlayerController.ownedActor = nullptr;
                    CurrentGame::getCurrentGame()->GetWorld()->StartRunningWorld();
                };
                if (ImGui::Button("Build")) {

                    BuildReflectedGame(CurrentGame::getCurrentGame());

                };
            }
            if (CurrentGame::getCurrentGame()->GetWorld()->isTickingEnabled) {
                if (ImGui::Button("Stop")) {
                    CurrentGame::getCurrentGame()->GetWorld()->isTickingEnabled = false;
                    CurrentGame::getCurrentGame()->GetWorld()->actors.clear();
                    CurrentGame::getCurrentGame()->GetWorld()->actors = worldEditorCopy.actors;
                    CurrentGame::getCurrentGame()->GetWorld()->currentPlayerController.ownedActor = nullptr;

                }
            }
         
            std::string countedFps = "FPS: " + std::to_string(1 / fpsCounterDelta);
            ImGui::Text(countedFps.c_str());

            std::string triangles = "Triangles: " + std::to_string(CurrentGame::getCurrentGame()->GetWorld()->GetWorldGeometry()->size() / 16);
            ImGui::Text(triangles.c_str());


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
            //shouldGameLoaderBeOpened = false;
            CurrentGame::setCurrentGame("E:/ReTToSbx/ReTToSbx.dll");
            worldEditorCopy = *CurrentGame::getCurrentGame()->GetWorld();
        }
        if (ImGui::Button("run spawn actor")) {
            CurrentGame::getCurrentGame()->RunVoidFunction("SpawnActorTest");
        };
       
        ImGui::End();
    }
}

void EditorInterface::CreateViewport()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding,ImVec2(0,0));
    ImGui::Begin("Viewport",(bool*)0,ImGuiWindowFlags_NoCollapse);
    viewportSize = ImGui::GetContentRegionAvail();
    viewportSizeMirror = ivec2(viewportSize.x, viewportSize.y);
    ImGui::Image((void*)viewportTexture->texture, viewportSize,ImVec2(0,1),ImVec2(1,0));
    ImGui::End();
    ImGui::PopStyleVar();
    
}

void EditorInterface::CreateActorBrowser()
{
    ImGui::Begin("Actors");
    if (CurrentGame::getCurrentGame()->GetWorld() != nullptr) {
        for (int i = 0; i < CurrentGame::getCurrentGame()->GetWorld()->actors.size(); i++) {
            std::string stringActor = typeid(CurrentGame::getCurrentGame()->GetWorld()->actors[i]).name();
            char* charActor = const_cast<char*>(stringActor.c_str());
            ImGuiTreeNodeFlags itemFlags = ((i == selectedActor) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_Leaf;
            bool item = ImGui::TreeNodeEx(charActor, itemFlags);
            if (ImGui::IsItemClicked()) {
                selectedActor = i;
            }
            if (item) {
                ImGui::TreePop();
            };
        }
        if (CurrentGame::getCurrentGame()->GetWorld()->actors.size() == 0) {
            selectedActor = -1;
        }
    }
    ImGui::End();
}

void EditorInterface::CreateActorProperties()
{
    ImGui::Begin("Actor Properties");
  
    if (CurrentGame::getCurrentGame()->GetWorld() != nullptr) {
        if (selectedActor != -1) {
            if (ImGui::TreeNode("Components")) {
                Actor* currentActor = CurrentGame::getCurrentGame()->GetWorld()->actors[selectedActor];
                for (int currentComponent = 0; currentComponent < currentActor->components.size(); currentComponent++) {

                    if (ImGui::TreeNode(std::string(std::to_string(currentComponent) +" : " + currentActor->components[currentComponent]->className).c_str())) {
                        for (int currentVariable = 0; currentVariable < currentActor->components[currentComponent]->variableRegistryNames.size(); currentVariable++) {
                            void* variable = currentActor->components[currentComponent]->variableRegistry[currentVariable];
                            std::string variableType = currentActor->components[currentComponent]->variableRegistryClass[currentVariable];
                            std::string variableNameStr = currentActor->components[currentComponent]->variableRegistryNames[currentVariable];

                            GenerateRegister(variableType, variableNameStr, variable);
                        }

                        ImGui::TreePop();
                    }
                }
                ImGui::TreePop();
            };

            for (int i = 0; i < CurrentGame::getCurrentGame()->GetWorld()->actors[selectedActor]->variableRegistry.size(); i++) {
              

                void* variable = CurrentGame::getCurrentGame()->GetWorld()->actors[selectedActor]->variableRegistry[i];
                std::string variableType = CurrentGame::getCurrentGame()->GetWorld()->actors[selectedActor]->variableRegistryClass[i];
                std::string variableNameStr = CurrentGame::getCurrentGame()->GetWorld()->actors[selectedActor]->variableRegistryNames[i];

                GenerateRegister(variableType, variableNameStr, variable);


            }
        }
    }
    ImGui::End();
}
void EditorInterface::GenerateRegister(std::string variableType, std::string variableNameStr, void* variable) {

    char* variableName = const_cast<char*>(variableNameStr.c_str());

    if (variableType == "float") {
        float* varPointer = static_cast<float*>(variable);
        ImGui::DragFloat(variableName, varPointer, 0.1);
    }
    else if (variableType == "bool") {
        bool* varPointer = static_cast<bool*>(variable);
        ImGui::Checkbox(variableName, varPointer);
    }
    else if (variableType == "int") {
        int* varPointer = static_cast<int*>(variable);
        ImGui::DragInt(variableName, varPointer, 0.1);
    }
    else if (variableType == "struct glm::vec<2,float,0>") {
        vec2* varPointer = static_cast<vec2*>(variable);
        ImGui::DragVec2(variableName, varPointer, 0.1);
    }
    /*else if (variableType == "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >") {
        std::string* varPointer = static_cast<std::string*>(variable);
        static char buf[255];
        strcpy(buf, varPointer->c_str());
        ImGui::InputText(variableName, buf, sizeof(buf));
        *varPointer = buf;
    }*/
    else if (variableType == "struct glm::vec<3,float,0>") {
        vec3* varPointer = static_cast<vec3*>(variable);
        ImGui::DragVec3(variableName, varPointer, 0.1);
    }
    else if (variableType == "struct glm::vec<4,float,0>") {
        vec4* varPointer = static_cast<vec4*>(variable);
        ImGui::DragVec4(variableName, varPointer, 0.1);
    }
    else {
        std::string unsupportedVariableNameStr = variableNameStr + " : Unsupported class";
        char* variableName = const_cast<char*>(unsupportedVariableNameStr.c_str());
        ImGui::Text(variableName);
    }
}
