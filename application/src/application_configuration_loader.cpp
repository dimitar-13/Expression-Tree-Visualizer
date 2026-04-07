#include "application_configuration_loader.h"
#include <iostream>
#include <fstream>

ConfigurationLoader::ConfigurationLoader()
{
    std::ifstream configuration_file("D:/c++/Expression Tree Visualizer/appConfig.json", std::ifstream::binary);

    if (!configuration_file.is_open())
    {
        std::cout << "Failed to open configuration file." << std::endl;
        return;
    }
    m_configuration = nlohmann::json::parse(configuration_file);
}

std::string ConfigurationLoader::LoadConfiguration(const std::string& configurationName)
{
    auto config = m_configuration.find(configurationName);

    if (config.value() == nullptr)
    {
        std::cout << "Configuration with name " << configurationName << " not found." << std::endl;
    }
    return config.value();
}
