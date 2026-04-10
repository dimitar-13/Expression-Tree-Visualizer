#include <GL/glew.h>
#include "window_class.h"
#include <iostream>
Window::Window(GLFWwindow* handle, size_t width, size_t height):
    m_handle(handle),
    m_windowWidth(width),
    m_windowHeight(height)
{
    glfwMakeContextCurrent(this->m_handle);
    this->SetUpGLFWCallbacks();
}

std::unique_ptr<Window> Window::TryCreateWindow(size_t width, size_t height, const std::string& window_name)
{
    GLFWmonitor* externalMonitor = nullptr;
    GLFWwindow* sharedWindow = nullptr;
    std::unique_ptr<Window> result = nullptr;

    if (!glfwInit())
    {
        return result;
    }
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    GLFWwindow* window_handle = glfwCreateWindow(width, height, window_name.c_str(), externalMonitor, sharedWindow);

    if (window_handle == nullptr)
    {
        return result;
    }

    result = std::unique_ptr<Window>(new Window(window_handle,width, height));

    return result;
}

Window::~Window()
{
    glfwDestroyWindow(this->m_handle);
    glfwTerminate();
}

void Window::SetUpGLFWCallbacks()
{
    glfwSetWindowUserPointer(this->m_handle, this);

    auto on_window_resize_callback_bind = [](GLFWwindow* w, int new_width, int new_height)
        {
            static_cast<Window*>(glfwGetWindowUserPointer(w))->OnWindowResize(new_width, new_height);
        };

    glfwSetWindowSizeCallback(this->m_handle, on_window_resize_callback_bind);
    
    auto on_window_close_callback_bind = [](GLFWwindow* w)
        {
            static_cast<Window*>(glfwGetWindowUserPointer(w))->OnWindowClose();
        };

    glfwSetWindowCloseCallback(this->m_handle, on_window_close_callback_bind);

}

void Window::OnWindowResize(int new_width, int new_height)
{
    this->m_windowWidth = new_width;
    this->m_windowHeight = new_height;
    this->m_windowResizeApplicationCallback(new_width, new_height);
}

void Window::OnWindowClose()
{
    this->m_isWindowClosed = true;
}

void APIENTRY Window::glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam)
{
    // Thank u `https://learnopengl.com/In-Practice/Debugging` <3

    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " << message << std::endl;

    switch (source)
    {
    case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
    case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
    case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
    } std::cout << std::endl;

    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
    case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
    case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
    case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
    case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
    case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
    case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
    } std::cout << std::endl;

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
    case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
    case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
    case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
    } std::cout << std::endl;
    std::cout << std::endl;
}
