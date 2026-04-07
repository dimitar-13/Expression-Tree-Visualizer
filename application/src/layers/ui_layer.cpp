#include "ui_layer.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <iostream>
#include "../../src/application.h"
#include <misc/cpp/imgui_stdlib.h>
#include <misc/cpp/imgui_stdlib.cpp>
#include <ExpressionValidator.h>
#include "constants/Configurations.h"


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

    static bool is_expression_valid = true;
    static std::string expression_validation_reason;
    ImGui::InputText("Expression", &this->m_expressionString, flags);
    if (!is_expression_valid)
    {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%s", expression_validation_reason.c_str());
    }

    if (ImGui::Button("Clear expression"))
    {
        this->m_expressionString.clear();
    }
    ImGui::SameLine();
    if (ImGui::Button("Generate tree"))
    {
        is_expression_valid = ExpressionValidator::IsExpressionValid(this->m_expressionString, expression_validation_reason);
        if (is_expression_valid)
        {
            this->m_graphicsLayer->GenerateTree(this->m_expressionString);
        }
    }
    ImGui::SameLine();

    if (ImGui::Button("Load default expression"))
    {
        this->m_expressionString = Application::GetApplication().GetConfiguration(Configurations::DefaultExpression);
    }
    ImGui::Separator();


    if (ImGui::Button("<"))
    {
        this->m_graphicsLayer->GoToPreviousState();
    }
    ImGui::SameLine();

    if (ImGui::Button(">"))
    {
        this->m_graphicsLayer->GoToNextState();
    }
    ImGui::Separator();


    std::string tree_postfix_expression = "";
    std::string tree_prefix_expression = "";
    std::string tree_expression = "";

    if (auto current_tree = this->m_graphicsLayer->GetFinalTree().lock())
    {
        tree_expression = this->m_graphicsLayer->GetCurrentExpression();
        tree_postfix_expression = current_tree->GetPostfix();
        tree_prefix_expression = current_tree->GetPrefix();
    }

    ImGui::Text("Tree Data");
    ImGui::Text("Expression:'%s'", tree_expression.c_str());
    ImGui::Text("Postfix expression:'%s'", tree_postfix_expression.c_str());
    ImGui::Text("Prefix expression:'%s'", tree_prefix_expression.c_str());

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
    this->m_expressionString = Application::GetApplication().GetConfiguration(Configurations::DefaultExpression);

    auto graphics_layer = Application::GetApplication().GetLayerByName(typeid(GraphicsLayer).name());

    if (!graphics_layer.expired())
    {
        this->m_graphicsLayer = std::dynamic_pointer_cast<GraphicsLayer>(graphics_layer.lock());
    }

    auto variable_limit = Application::GetApplication().GetConfiguration(Configurations::ExpressionVariableLimit);

    ExpressionValidator::SetExpressionCharacterLimit(std::stoi(variable_limit));

}
