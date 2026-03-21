#include <GL/glew.h>
#include "application.h"
#include<iostream>

std::unique_ptr<Application> Application::CreateApplication(size_t application_width, size_t application_height, const std::string& application_name)
{
    std::unique_ptr<Application> result = nullptr;

    if (glewInit() == GL_FALSE)
    {
        std::cout << "Failed to initialize GLEW" << '\n';
        return result;
    }

    glewExperimental = GL_TRUE;
    
    std::unique_ptr<Window> application_window = Window::TryCreateWindow(application_width, application_height, application_name);

    if (application_window == nullptr)
    {
        std::cout << "Failed to create window." << '\n';
        return result;
    }

    result = std::unique_ptr<Application>(new Application(std::move(application_window)));

    return result;
}

void Application::Run()
{

    while (!this->m_Window->ShouldWindowClose())
    {
        this->m_Window->PollEvents();

        glClearColor(1, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        this->m_Window->SwapBuffer();

    }
}

Application::Application(std::unique_ptr<Window> window):
    m_Window(std::move(window))
{
    Size window_current_size = this->m_Window->GetWindowSize();

    glViewport(0, 0, window_current_size.x, window_current_size.y);

}
