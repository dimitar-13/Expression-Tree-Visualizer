#include "graphics_layer.h"
#include <iostream>
#include "graphics/shader_class.h"
#include <array>
#include "application.h"
#include <glm/gtc/matrix_transform.hpp>

static constexpr size_t kWindowLength = 1200;

static constexpr glm::vec2 kSize = { kWindowLength,kWindowLength };

static constexpr float kStartupHeight = 1000.f;

static constexpr glm::vec2 KViewportMin = -(kSize / 2.f);
static constexpr glm::vec2 KViewportMax = kSize / 2.f;


void GraphicsLayer::Initialize()
{
    batch_renderer = std::make_unique<BatchPipeline>();
    Size application_window_size = Application::GetApplication().GetWindow().GetWindowSize();

    glm::vec2 window_size_to_position = { application_window_size.x,application_window_size.y };
    batch_renderer->GetLineShader().SetUniform2D(kWindowSizeUniformName, window_size_to_position);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_OrthographicProjection = glm::ortho(0.f, kSize.x,0.f, kSize.y,-1.0f,1.0f);

    batch_renderer->GetLineShader().SetUniformMat4x4(kProjectionUniformName, m_OrthographicProjection);
    batch_renderer->GetCircleShader().SetUniformMat4x4(kProjectionUniformName, m_OrthographicProjection);

    GenerateTree(Application::kDefaultExpression);
}

void GraphicsLayer::Update()
{

}

void GraphicsLayer::Draw()
{
    auto current_tree = this->m_expressionTreeStateManager->GetCurrentState().lock();

    if (current_tree->isTreeConnected())
    {
        SubmitTreeNode(this->m_expressionTreeStateManager->GetCurrentState().lock()->GetTreeTop(), glm::vec2(kSize.x/2.f, kStartupHeight), kSize/glm::vec2(2.f));
    }
    else
    {
        auto top_nodes = this->m_expressionTreeStateManager->GetCurrentState().lock()->GetTreeTopNodes();
        size_t counter = 1;

        float box_width_height = static_cast<float>(kWindowLength) / static_cast<float>(top_nodes.size());
        glm::vec2 box_size = { box_width_height / 2.f,box_width_height};

        while (top_nodes.size() > 0)
        {
            glm::vec2 box_center = glm::vec2(box_width_height,0)* glm::vec2(counter) - glm::vec2(box_size.x, -kStartupHeight);
            SubmitTreeNode(top_nodes.front(), box_center, box_size);
            top_nodes.pop();
            counter++;
        }
    }

    batch_renderer->Draw(this->m_OrthographicProjection);

    batch_renderer->FlushBatch();
}

void GraphicsLayer::OnScreenResize(int newSize, int newWidth)
{
    batch_renderer->GetCircleShader().UserProgram();
    batch_renderer->GetCircleShader().SetUniform2D(kWindowSizeUniformName, glm::vec2{ newSize,newWidth });
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
    ExpressionTreeBuilder tree_builder(expression);
    auto new_tree_manager = tree_builder.GetStateManager().lock();
    this->m_expressionTreeStateManager = new_tree_manager;
    this->m_expressionTreeStateManager->GetLastState();
}

void GraphicsLayer::SubmitTreeNode(std::shared_ptr<Node> current_node, glm::vec2 center, const glm::vec2& half_of_size, int depth)
{
    depth++;
    if (current_node == nullptr)
        return;


    batch_renderer->PushCircle(center);
    batch_renderer->PushCharacter(center, current_node->symbol);

    glm::vec2 next_offset = { half_of_size.x /2.f , half_of_size.y/2.2f};



    if (current_node->pLeftNode)
    {
        glm::vec2 next_center = center - next_offset;

        batch_renderer->PushLine(next_center, center);
        this->SubmitTreeNode(current_node->pLeftNode, next_center, next_offset, depth);
    }
    if (current_node->pRightNode)
    {
        glm::vec2 next_node_position_right = center + glm::vec2{ next_offset.x, -next_offset.y };

        batch_renderer->PushLine(center,next_node_position_right);
        this->SubmitTreeNode(current_node->pRightNode, next_node_position_right, next_offset, depth);
    }
}