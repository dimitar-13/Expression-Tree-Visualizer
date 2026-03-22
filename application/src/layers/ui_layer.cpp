#include "ui_layer.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <iostream>
#include "../../src/application.h"

size_t UILayer::kExpressionStringLength = 50;

void UILayer::Update()
{
}

void UILayer::Draw()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::InputText("Expression", &this->m_expressionString[0], kExpressionStringLength);

    if (ImGui::Button("Clear expressionn"))
    {
        this->m_expressionString.clear();
    }
    ImGui::SameLine();

    if (ImGui::Button("Generate tree"))
    {
        std::cout << "Button was pressed!" << '\n';
    }
    ImGui::Separator();


    if (ImGui::Button("Previous"))
    {
        std::cout << "Undo button was pressed!" << '\n';
    }
    ImGui::SameLine();

    if (ImGui::Button("Next"))
    {
        std::cout << "Next button was pressed!" << '\n';

        this->m_graphicsLayer->TestMethod();
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

    this->m_expressionString.resize(kExpressionStringLength);

    auto graphics_layer = Application::GetApplication().GetLayerByName(typeid(GraphicsLayer).name());

    if (!graphics_layer.expired())
    {
        this->m_graphicsLayer = std::dynamic_pointer_cast<GraphicsLayer>(graphics_layer.lock());
    }

}
