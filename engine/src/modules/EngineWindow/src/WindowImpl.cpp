#include "EngineWindow/PreInclude.hpp"
#include "EngineWindow/WindowImpl.hpp"
#include "EngineCores/EngineCores.hpp"

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>


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

        glfwMakeContextCurrent(window_);

        glfwSetWindowCloseCallback(window_, [](GLFWwindow* window)
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        });
    } 

    void WindowImpl::ImGuiBackendInit() 
    {
        ImGui_ImplGlfw_InitForOpenGL(window_, true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    void WindowImpl::OnUpdateBegin(Timestep ts)
    {
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void WindowImpl::OnUpdateEnd(Timestep ts)
    {
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window_, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window_);
    }

    void WindowImpl::Release()
    {
        glfwTerminate();
    }

    void WindowImpl::ImGuiBackendRelease()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
    }

    bool WindowImpl::ShouldClose()
    {
        return glfwWindowShouldClose(window_);
    }
} // namespace ntt
