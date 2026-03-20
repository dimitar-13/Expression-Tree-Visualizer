#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main()
{
    constexpr int kWindowWidth = 500, kWindowHeight = 700;
    char* window_name = "Test window";

    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << '\n';
        return -1;
    }


    GLFWwindow* window_handle = glfwCreateWindow(kWindowWidth, kWindowHeight, window_name, NULL, NULL);

    if (window_handle == nullptr)
    {
        std::cout << "Failed to create GLFW window" << '\n';
        return -1;
    }

    if (glewInit() == GL_FALSE)
    {
        std::cout << "Failed to initialize GLEW" << '\n';
        return -1;
    }

    glewExperimental = GL_TRUE;

    glfwMakeContextCurrent(window_handle);

    glViewport(0, 0, kWindowWidth, kWindowHeight);

    while (!glfwWindowShouldClose(window_handle))
    {
        glfwPollEvents();

        glClearColor(1, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window_handle);

    }


    std::cout << "Executed succsessfully!" << '\n';

    return 1;
}