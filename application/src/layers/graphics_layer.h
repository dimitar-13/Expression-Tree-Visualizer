#pragma once
#include "layer.h"
#include "graphics/batch_renderer.h"
#include  "ExpressionTreeBuilder.h"
#include "helpers/treeSymmetryEnum.h"
class GraphicsLayer : public Layer
{
public:
    void Initialize() override;
    void Update()override;
    void Draw()override;
    void OnScreenResize(int newSize, int newWidth) override;
    void GoToPreviousState();
    void GoToNextState();
    void GenerateTree(const std::string& expression);
private:
    void SubmitTreeNode(std::shared_ptr<Node> current_node, glm::vec2 center,const glm::vec2& half_of_size, int depth = 0);
private:

    std::shared_ptr<StateManager<ExpressionTree>> m_expressionTreeStateManager;

    std::unique_ptr<BatchPipeline> batch_renderer;
    const char* kWindowSizeUniformName = "u_ScreenSize";
    const char* kProjectionUniformName = "u_projection";
    glm::mat4 m_OrthographicProjection;
};