#include "graphics_layer.h"
#include <iostream>
#include "graphics/shader_class.h"
#include <array>
#include "application.h"

void GraphicsLayer::Initialize()
{
    batch_renderer = std::make_unique<BatchPipeline>();
    Size application_window_size = Application::GetApplication().GetWindow().GetWindowSize();

    Position2D window_size_to_position = { application_window_size.x,application_window_size.y };
    batch_renderer->GetShader().SetUniform2D(kWindowSizeUniformName, window_size_to_position);

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

void GraphicsLayer::OnScreenResize(int newSize, int newWidth)
{

    batch_renderer->GetShader().SetUniform2D(kWindowSizeUniformName, Position2D{ static_cast<float>(newSize), static_cast<float>(newWidth) });
}

void GraphicsLayer::TestMethod()
{
    std::cout << "This method is called from UI " << '\n';
}
