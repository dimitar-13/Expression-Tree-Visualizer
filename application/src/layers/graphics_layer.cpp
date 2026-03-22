#include "graphics_layer.h"
#include <iostream>
#include "graphics/shader_class.h"
#include <array>

void GraphicsLayer::Initialize()
{
    batch_renderer = std::make_unique<BatchPipeline>();
}

void GraphicsLayer::Update()
{

}

void GraphicsLayer::Draw()
{

    batch_renderer->PushCircle(Position2D{0,0});

    batch_renderer->Draw();

    batch_renderer->FlushBatch();

}

void GraphicsLayer::TestMethod()
{
    std::cout << "This method is called from UI " << '\n';
}
