#include <GL/glew.h>
#include "application.h"
#include<iostream>
#include "layers/ui_layer.h"
#include "layers/graphics_layer.h"

bool Application::TryInitializeApplicationDependencies(size_t application_width, size_t application_height, const std::string& application_name)
{

    if (glewInit() == GL_FALSE)
    {
        std::cout << "Failed to initialize GLEW" << '\n';
        return false;
    }

    glewExperimental = GL_TRUE;
    
    std::unique_ptr<Window> application_window = Window::TryCreateWindow(application_width, application_height, application_name);

    if (application_window == nullptr)
    {
        std::cout << "Failed to create window." << '\n';
        return false;
    }

    auto& instance = Application::GetApplication();
    instance.m_Window = std::move(application_window);

    return true;
}

Application& Application::GetApplication()
{
    static Application instance;

    return instance;
}

std::weak_ptr<Layer> Application::GetLayerByName(std::string layer_name)
{
    if (this->m_layerNameMap.find(layer_name) != this->m_layerNameMap.end())
    {
        return this->m_layerNameMap[layer_name];
    }

    return std::weak_ptr<Layer>();
}

void Application::InitApplication()
{
    Size window_current_size = this->m_Window->GetWindowSize();

    glViewport(0, 0, window_current_size.x, window_current_size.y);

    auto ui_layer = std::make_shared<UILayer>();
    auto drawing_layer = std::make_shared<GraphicsLayer>();


    this->m_layerNameMap =
    {
        {typeid(ui_layer).name()      ,ui_layer},
        {typeid(drawing_layer).name() ,drawing_layer},
    };

    for (auto layer_name_pair : this->m_layerNameMap)
    {
        layer_name_pair.second->Initialize();
    }
}

void Application::Run()
{

    while (!this->m_Window->ShouldWindowClose())
    {
        this->m_Window->PollEvents();

        glClearColor(1, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto layer_name_pair : this->m_layerNameMap)
        {
            layer_name_pair.second->Draw();
        }

        this->m_Window->SwapBuffer();

    }
}

Application::~Application()
{
}

