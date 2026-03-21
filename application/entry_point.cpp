#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "src/application.h"



int main()
{
    constexpr int kWindowWidth = 500, kWindowHeight = 700;
    char* window_name = "Test window";

    std::unique_ptr<Application> application = Application::CreateApplication(kWindowWidth, kWindowHeight, window_name);
    
    if (application == nullptr)
    {
        std::cout << "Failed to create valid application." << '\n';
        return -1;
    }

    application->Run();

    return 1;
}
