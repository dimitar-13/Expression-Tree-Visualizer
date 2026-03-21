#include "window_class.h"

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
}

void Window::OnWindowClose()
{
    this->m_isWindowClosed = true;
}
