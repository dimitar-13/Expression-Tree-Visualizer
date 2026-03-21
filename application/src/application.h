#pragma once
#include<memory>
#include<string>
#include "window_class.h"

class Application
{
public:
    static std::unique_ptr<Application> CreateApplication(size_t application_width, size_t application_height,const std::string& application_name);

    void Run();
    ~Application() = default;
private:
    Application(std::unique_ptr<Window> window);

    void RenderUI();
    void RenderScene();

    void InitializeImGUI();

private:
    std::string ui_expressionString;
    std::unique_ptr<Window> m_Window;
};