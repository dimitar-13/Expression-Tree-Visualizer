#include "graphics_layer.h"
#include <iostream>
#include "graphics/shader_class.h"
#include <array>
#include "application.h"
#include <glm/gtc/matrix_transform.hpp>

static constexpr glm::vec2 kSize = { 800,800 };

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

    m_OrthographicProjection = glm::ortho(KViewportMin.x, KViewportMax.x, KViewportMin.y, KViewportMax.y,-1.0f,1.0f);

    batch_renderer->GetLineShader().SetUniformMat4x4(kProjectionUniformName, m_OrthographicProjection);
    batch_renderer->GetCircleShader().SetUniformMat4x4(kProjectionUniformName, m_OrthographicProjection);

    // (a - b) ^ (c + d)
    // (1-2)^(2-5)
    // 1+1+1+1 
    GenerateTree("(1-2)^(2-5)");
}

void GraphicsLayer::Update()
{

}

void GraphicsLayer::Draw()
{    
    SubmitTreeNode(m_ExpressionTree->GetTreeTop(), this->m_TreeBaseLine);

    batch_renderer->Draw();

    batch_renderer->FlushBatch();
}

void GraphicsLayer::OnScreenResize(int newSize, int newWidth)
{

    batch_renderer->GetLineShader().SetUniform2D(kWindowSizeUniformName, glm::vec2{ newSize,newWidth });
}

void GraphicsLayer::TestMethod()
{
    std::cout << "This method is called from UI " << '\n';
}

void GraphicsLayer::GenerateTree(const std::string& expression)
{
    ExpressionTreeBuilder tree_builder(expression);
    this->m_ExpressionTree = tree_builder.GetTree().lock();

    constexpr float kTreeBaseLineVerticalPosition = 300.f;
    constexpr float kTreeBaseLineHorizontalPosition = 250.f;
    TreeSymmetry tree_symmetry = GetTreeSymmetry();

    switch (tree_symmetry)
    {
        case TreeSymmetry::kSymmetrical :
        this->m_TreeBaseLine = { 0.f, kTreeBaseLineVerticalPosition };
           break;
        
        case TreeSymmetry::kLeftHeavy:
            this->m_TreeBaseLine = { -kTreeBaseLineHorizontalPosition, kTreeBaseLineVerticalPosition };
            break;

        case TreeSymmetry::kRightHeavy:
            this->m_TreeBaseLine = { kTreeBaseLineHorizontalPosition, kTreeBaseLineVerticalPosition };
            break;
    }
}

void GraphicsLayer::SubmitTreeNode(std::shared_ptr<Node> current_node, glm::vec2 base_line, int depth)
{
    depth++;
    if (current_node == nullptr)
        return;


    batch_renderer->PushCircle(base_line);
    
    float offset_value = 150.f / static_cast<float>(depth);

    if (current_node->pLeftNode)
    {
        glm::vec2 next_node_position = base_line + glm::vec2{ -offset_value, -offset_value };
        batch_renderer->PushLine(next_node_position, base_line);
        this->SubmitTreeNode(current_node->pLeftNode, next_node_position, depth);
    }
    if (current_node->pRightNode)
    {
        glm::vec2 next_node_position_right = base_line + glm::vec2{ offset_value, -offset_value };

        batch_renderer->PushLine(base_line,next_node_position_right);
        this->SubmitTreeNode(current_node->pRightNode, next_node_position_right, depth);
    }
}

TreeSymmetry GraphicsLayer::GetTreeSymmetry()
{
    int total_left_connections = 0;
    int total_right_connections = 0;

    auto left_path_node = m_ExpressionTree->GetTreeTop();
    auto right_path_node = m_ExpressionTree->GetTreeTop();

    while (left_path_node->pLeftNode && right_path_node->pRightNode)
    {
        left_path_node = left_path_node->pLeftNode;
        total_left_connections = left_path_node == nullptr ? total_left_connections : total_left_connections + 1;

        right_path_node = right_path_node->pRightNode;
        total_right_connections = right_path_node == nullptr ? total_right_connections : total_right_connections + 1;
    }

    int node_diff = total_left_connections - total_right_connections;

    return node_diff == 0 ? TreeSymmetry::kSymmetrical : node_diff > 0 ? TreeSymmetry::kLeftHeavy : TreeSymmetry::kRightHeavy;
}
