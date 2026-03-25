#pragma once
#include "layer.h"
#include "graphics/batch_renderer.h"
class GraphicsLayer : public Layer
{
public:
    void Initialize() override;
    void Update()override;
    void Draw()override;
    void OnScreenResize(int newSize, int newWidth) override;
    void TestMethod();
private:
    std::unique_ptr<BatchPipeline> batch_renderer;
    const char* kWindowSizeUniformName = "u_ScreenSize";
};