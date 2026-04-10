#pragma once
#include <string>
#include <nlohmann/json.hpp>

class ConfigurationLoader
{
public:
    ConfigurationLoader();
    std::string LoadConfiguration(const std::string& configurationName);

private:
    nlohmann::json m_configuration;
};