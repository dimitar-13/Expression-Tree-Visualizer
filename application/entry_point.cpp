#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "src/application.h"



int main()
{
    constexpr int kWindowWidth = 500, kWindowHeight = 700;
    char* window_name = "Test window";

   
    if (!Application::TryInitializeApplicationDependencies(kWindowWidth, kWindowHeight, window_name))
    {
        std::cout << "Failed to create valid application." << '\n';
        return -1;
    }
    Application::GetApplication().InitApplication();


    Application::GetApplication().Run();

    return 1;
}
