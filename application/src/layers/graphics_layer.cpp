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
    batch_renderer->GetShader().SetUniform2D(kWindowSizeUniformName, window_size_to_position);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_OrthographicProjection = glm::ortho(KViewportMin.x, KViewportMax.x, KViewportMin.y, KViewportMax.y,-1.0f,1.0f);

    batch_renderer->GetShader().SetUniformMat4x4(kProjectionUniformName, m_OrthographicProjection);

}

void GraphicsLayer::Update()
{

}

void GraphicsLayer::Draw()
{
    PerSceneLogic();

    batch_renderer->Draw();

    batch_renderer->FlushBatch();
}

void GraphicsLayer::OnScreenResize(int newSize, int newWidth)
{

    batch_renderer->GetShader().SetUniform2D(kWindowSizeUniformName, glm::vec2{ newSize,newWidth });
}

void GraphicsLayer::TestMethod()
{
    std::cout << "This method is called from UI " << '\n';
}

void GraphicsLayer::PerSceneLogic()
{
    // batch_renderer->PushCircle(Position2D{ 0,0 });
    batch_renderer->PushCircle(glm::vec2{ 0,0 });
    // batch_renderer->PushCircle(Position2D{ .001,0 });
}
