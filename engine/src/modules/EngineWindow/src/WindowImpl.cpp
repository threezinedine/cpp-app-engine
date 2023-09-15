#include "EngineWindow/PreInclude.hpp"
#include "EngineWindow/WindowImpl.hpp"
#include "EngineCores/EngineCores.hpp"

#include <imgui.h>


namespace ntt
{
    Ref<Window> WindowImpl::CreateRef(int width, int height, const char* title)
    {
        return std::make_shared<WindowImpl>(width, height, title);
    }

    Ref<Window> WindowImpl::CreateRef(const char* title)
    {
        return std::make_shared<WindowImpl>(title);
    }


    WindowImpl::WindowImpl(const char* title)
        : width_(-1), height_(-1), title_(title)
    {

    }

    WindowImpl::WindowImpl(int width, int height, const char* title)
        : width_(width), height_(height), title_(title)
    {

    }

    WindowImpl::~WindowImpl()
    {

    }

    void WindowImpl::Init()
    {
        if (!glfwInit())
        {
            exit(-1);
        }

        if (width_ == -1)
        {
            window_ = glfwCreateWindow(800, 600, title_, nullptr, nullptr);
            glfwMaximizeWindow(window_);
        }
        else 
        {
            window_ = glfwCreateWindow(width_, height_, title_, nullptr, nullptr);
        }

        glfwSetWindowCloseCallback(window_, [](GLFWwindow* window)
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        });
    } 

    void WindowImpl::ImGuiBackendInit() 
    {

    }

    void WindowImpl::OnUpdateBegin(Timestep ts)
    {
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }

    void WindowImpl::OnUpdateEnd(Timestep ts)
    {
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }

    void WindowImpl::Release()
    {
        glfwTerminate();
    }

    void WindowImpl::ImGuiBackendRelease()
    {
        
    }

    bool WindowImpl::ShouldClose()
    {
        return glfwWindowShouldClose(window_);
    }
} // namespace ntt
