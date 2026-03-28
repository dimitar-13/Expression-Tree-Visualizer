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
    void TestMethod();
    void GenerateTree(const std::string& expression);
private:
    void SubmitTreeNode(std::shared_ptr<Node> current_node, glm::vec2 base_line, int depth = 0);
    TreeSymmetry GetTreeSymmetry();
private:
    glm::vec2 m_TreeBaseLine = { 0,0 };

    std::shared_ptr<ExpressionTree> m_ExpressionTree;
    std::unique_ptr<BatchPipeline> batch_renderer;
    const char* kWindowSizeUniformName = "u_ScreenSize";
    const char* kProjectionUniformName = "u_projection";
    glm::mat4 m_OrthographicProjection;
};