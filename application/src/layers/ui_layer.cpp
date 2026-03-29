#include "ui_layer.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <iostream>
#include "../../src/application.h"
#include <misc/cpp/imgui_stdlib.h>
#include <misc/cpp/imgui_stdlib.cpp>

size_t UILayer::kExpressionStringLength = 50;

ImGuiInputTextFlags flags = ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_AlwaysOverwrite;

void UILayer::Update()
{
}

void UILayer::Draw()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    ImGui::InputText("Expression", &this->m_expressionString, flags);

    if (ImGui::Button("Clear expression"))
    {
        this->m_expressionString.clear();
    }
    ImGui::SameLine();

    if (ImGui::Button("Generate tree"))
    {
        this->m_graphicsLayer->GenerateTree(this->m_expressionString);
    }
    ImGui::SameLine();

    if (ImGui::Button("Load default expression"))
    {
        this->m_expressionString = Application::kDefaultExpression;
    }
    ImGui::Separator();


    if (ImGui::Button("Previous"))
    {
        this->m_graphicsLayer->GoToPreviousState();
    }
    ImGui::SameLine();

    if (ImGui::Button("Next"))
    {
        this->m_graphicsLayer->GoToNextState();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UILayer::Initialize()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplGlfw_InitForOpenGL(Application::GetApplication().GetWindow().GetWindowHandle(), true);
    ImGui_ImplOpenGL3_Init();

    this->m_expressionString.reserve(kExpressionStringLength);
    this->m_expressionString = Application::kDefaultExpression;

    auto graphics_layer = Application::GetApplication().GetLayerByName(typeid(GraphicsLayer).name());

    if (!graphics_layer.expired())
    {
        this->m_graphicsLayer = std::dynamic_pointer_cast<GraphicsLayer>(graphics_layer.lock());
    }

}
