#include "graphics_layer.h"
#include <iostream>
#include "graphics/shader_class.h"

static Shader test_shader("D:/c++/Expression Tree Visualizer/application/shaders/test_shader.glsl");

void GraphicsLayer::Initialize()
{

}

void GraphicsLayer::Update()
{

}

void GraphicsLayer::Draw()
{
}

void GraphicsLayer::TestMethod()
{
    std::cout << "This method is called from UI " << '\n';
}
