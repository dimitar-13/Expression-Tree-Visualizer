#pragma once
#include <memory>
#include <GLFW/glfw3.h>
#include <string>

struct Size
{
    size_t x;
    size_t y;
};

class Window
{
public:
    static std::unique_ptr<Window> TryCreateWindow(size_t width, size_t height, const std::string& window_name);

    Size GetWindowSize()const { return Size{ m_windowWidth,m_windowHeight }; }
    bool ShouldWindowClose()const { return this->m_isWindowClosed; }
    void SwapBuffer()const { return glfwSwapBuffers(this->m_handle); }
    void PollEvents()const { return glfwPollEvents(); }
    
    ~Window();
private:
    Window(GLFWwindow* handle,size_t width, size_t height);

    void SetUpGLFWCallbacks();
    void OnWindowResize(int new_width, int new_height);
    void OnWindowClose();
private:
    size_t m_windowWidth;
    size_t m_windowHeight;
    bool m_isWindowClosed = false;
    GLFWwindow* m_handle;
};