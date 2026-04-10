#pragma once
#include<memory>
#include<string>
#include "window_class.h"
#include "layers/layer.h"
#include <unordered_map>
#include "application_configuration_loader.h"

class Application
{
public:
    static bool TryInitializeApplicationDependencies(size_t application_width, size_t application_height,const std::string& application_name);
    static Application& GetApplication();

    std::string GetConfiguration(const std::string& configuration_name) { return m_configurationLoader.LoadConfiguration(configuration_name); }

    const Window& GetWindow()const { return *m_Window; }
    std::weak_ptr<Layer> GetLayerByName(const std::string& layer_name);
    void InitApplication();
    void Run();
    ~Application();
private:
    Application() = default;
    Application(const Application& other) = delete;
    void OnWindowResizeCallback(int new_widht, int new_hight);
private:
    std::string ui_expressionString;
    std::unordered_map<std::string,std::shared_ptr<Layer>> m_layerNameMap;
    std::unique_ptr<Window> m_Window;
    ConfigurationLoader m_configurationLoader;
};