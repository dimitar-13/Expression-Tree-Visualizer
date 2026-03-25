#pragma once
#include "layer.h"
#include "graphics/batch_renderer.h"
#include  "ExpressionTreeBuilder.h"
class GraphicsLayer : public Layer
{
public:
    void Initialize() override;
    void Update()override;
    void Draw()override;
    void OnScreenResize(int newSize, int newWidth) override;
    void TestMethod();
private:
    void PerSceneLogic();
private:
    std::unique_ptr<ExpressionTreeBuilder> m_treeBuilder;
    std::unique_ptr<BatchPipeline> batch_renderer;
    const char* kWindowSizeUniformName = "u_ScreenSize";
    const char* kProjectionUniformName = "u_projection";
    glm::mat4 m_OrthographicProjection;
};