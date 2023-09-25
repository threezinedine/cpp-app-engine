#include <GL/glew.h>
#include <iostream>
#include "EngineWindow/PreInclude.hpp"
#include "EngineWindow/WindowImpl.hpp"
#include "EngineCores/EngineCores.hpp"

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <opencv2/opencv.hpp>


#define ERROR() CheckError(__FILE__, __LINE__)
static void CheckError(const char* file, int line)
{
    GLenum error;
    if ((error = glGetError()) != GL_NO_ERROR) {
        switch (error) {
            case GL_INVALID_ENUM:
                std::cerr << "OpenGL Error (Enum) at " << file << ":" << line << ": GL_INVALID_ENUM" << std::endl;
                break;
            case GL_INVALID_VALUE:
                std::cerr << "OpenGL Error (Value) at " << file << ":" << line << ": GL_INVALID_VALUE" << std::endl;
                break;
            case GL_INVALID_OPERATION:
                std::cerr << "OpenGL Error (Operation) at " << file << ":" << line << ": GL_INVALID_OPERATION" << std::endl;
                break;
            case GL_OUT_OF_MEMORY:
                std::cerr << "OpenGL Error (Memory) at " << file << ":" << line << ": GL_OUT_OF_MEMORY" << std::endl;
                break;
            default:
                std::cerr << "OpenGL Error (Unknown) at " << file << ":" << line << ": Unknown error" << std::endl;
                break;
        }
    }
}


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
            std::cout << "Here" << std::endl;
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
        ERROR();

        if (glewInit() != GLEW_OK)
        {
            std::cout << "Here";
            glfwTerminate();
            exit(-1);
        }

        ERROR();
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
