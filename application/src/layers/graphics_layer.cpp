#include "graphics_layer.h"
#include <iostream>
#include "graphics/shader_class.h"
#include <array>
#include "application.h"
#include <glm/gtc/matrix_transform.hpp>
#include "constants/Configurations.h"
#include "helpers/ExpressionConverter.h"


void GraphicsLayer::Initialize()
{
    batch_renderer = std::make_unique<BatchPipeline>();
    Size application_window_size = Application::GetApplication().GetWindow().GetWindowSize();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int window_length = std::stoi(Application::GetApplication().GetConfiguration(Configurations::WindowLength));

    m_ProjectionSize = { window_length,window_length };

    OnScreenResize(application_window_size.x, application_window_size.y);

    m_bottomPadding = std::stof(Application::GetApplication().GetConfiguration(Configurations::BottomPadding));

    GenerateTree(Application::GetApplication().GetConfiguration(Configurations::DefaultExpression));
}

void GraphicsLayer::Update()
{

}

void GraphicsLayer::Draw()
{
    auto current_tree = this->m_expressionTreeStateManager->GetCurrentState().lock();

    float circle_radius = std::stof(Application::GetApplication().GetConfiguration(Configurations::InitialCircleRadius));
    float startup_height = std::stof(Application::GetApplication().GetConfiguration(Configurations::NodeStartupHeight));


    if (current_tree->isTreeConnected())
    {
        if (auto tree_top = this->m_expressionTreeStateManager->GetCurrentState().lock()->GetTreeTop())
        {
            size_t tree_depth = current_tree->GetDepth();

            tree_depth = tree_depth % 2 == 0 ? tree_depth + 1 : tree_depth;
            size_t vertical_offset = (startup_height / tree_depth) - m_bottomPadding;

            this->SubmitTreeNode(tree_top, glm::vec2(m_ProjectionSize.x / 2.f, startup_height),
                                           glm::vec2(m_ProjectionSize.x / 2.f, vertical_offset),
                                           circle_radius);
        }
    }
    else
    {
        auto top_nodes = this->m_expressionTreeStateManager->GetCurrentState().lock()->GetTreeTopNodes();
        size_t counter = 1;

        float box_width_height = static_cast<float>(m_ProjectionSize.x) / static_cast<float>(top_nodes.size());

        for (auto node : top_nodes)
        {
            size_t tree_depth = current_tree->GetDepth(node);
            tree_depth = tree_depth % 2 == 0 ? tree_depth + 1 : tree_depth;

            size_t vertical_offset = (startup_height / tree_depth) - m_bottomPadding;
            glm::vec2 box_size = { box_width_height / 2.f,vertical_offset };

            glm::vec2 box_center = glm::vec2(box_width_height,0)* glm::vec2(counter) - glm::vec2(box_size.x, -startup_height);
            SubmitTreeNode(node, box_center, box_size, circle_radius);
            counter++;
        }
    }

    this->batch_renderer->Draw();

    this->batch_renderer->FlushBatch();
}

void GraphicsLayer::OnScreenResize(int newWidth, int newHeight)
{
    int window_length = std::stoi(Application::GetApplication().GetConfiguration(Configurations::WindowLength));

    float aspect = static_cast<float>(newWidth) / static_cast<float>(newHeight);
    if (aspect > 1.f)
    {
        this->m_ProjectionSize.x = window_length * aspect;
    }
    else if (aspect < 1.f)
    {
        this->m_ProjectionSize.y = window_length / aspect;
    }

    m_OrthographicProjection = glm::ortho(0.f, m_ProjectionSize.x, 0.f, m_ProjectionSize.y, -1.0f, 1.0f);
    
    this->batch_renderer->SetProjectionMatrix(m_OrthographicProjection);
}

void GraphicsLayer::GoToPreviousState()
{
    this->m_expressionTreeStateManager->GetPreviousState();
}

void GraphicsLayer::GoToNextState()
{
    this->m_expressionTreeStateManager->GetNextState();
}


void GraphicsLayer::GenerateTree(const std::string& expression)
{
    this->m_CurrentExpression = expression;
    ExpressionConverter::ConvertExpressionNumbersToLetters(this->m_CurrentExpression);

    ExpressionTreeBuilder tree_builder(this->m_CurrentExpression);
    auto new_tree_manager = tree_builder.GetStateManager().lock();
    this->m_expressionTreeStateManager = new_tree_manager;
    this->m_expressionTreeStateManager->GetLastState();
}

void GraphicsLayer::SubmitTreeNode(std::shared_ptr<Node> current_node, glm::vec2 center, const glm::vec2& offset, float node_radius)
{
    if (current_node == nullptr)
        return;

    batch_renderer->PushCircle(center,glm::vec2(node_radius));
    batch_renderer->PushCharacter(center, current_node->symbol, glm::vec2(node_radius -10.f));

    glm::vec2 next_offset = { offset.x /2.f , offset.y};

    float next_node_radius = node_radius - 2.f;

    if (current_node->pLeftNode)
    {
        glm::vec2 next_center = center - next_offset;

        batch_renderer->PushLine(next_center, center);
        this->SubmitTreeNode(current_node->pLeftNode, next_center, next_offset, next_node_radius);
    }
    if (current_node->pRightNode)
    {
        glm::vec2 next_node_position_right = center + glm::vec2{ next_offset.x, -next_offset.y };

        batch_renderer->PushLine(center,next_node_position_right);
        this->SubmitTreeNode(current_node->pRightNode, next_node_position_right, next_offset, next_node_radius);
    }
}