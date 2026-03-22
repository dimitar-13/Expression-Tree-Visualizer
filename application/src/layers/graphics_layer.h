#pragma once
#include "layer.h"
#include "graphics/batch_renderer.h"
class GraphicsLayer : public Layer
{
public:
    void Initialize() override;
    void Update()override;
    void Draw()override;

    void TestMethod();
private:
    std::unique_ptr<BatchPipeline> batch_renderer;
};