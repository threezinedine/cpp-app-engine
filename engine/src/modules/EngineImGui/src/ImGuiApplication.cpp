#include "EngineImGui/PreInclude.hpp"
#include "EngineImGui/ImGuiApplication.hpp"
#include "EngineWindow/EngineWindow.hpp"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include "EngineImGui/ImGuiWindow.hpp"
#include "EngineThreading/EngineThreading.hpp"

#include <iostream>
#include <glfw/glfw3.h>
#define HERE() std::cout << "Line: " << __LINE__ << std::endl << "File: " << __FILE__ << std::endl
#define HERE_MSG(msg) std::cout << "Message: " << (msg) << " Line: " << __LINE__ << std::endl << "File: " << __FILE__ << std::endl

#ifdef REMOVE_ERROR
    #define ERROR() CheckError(__FILE__, __LINE__)
#else 
    #define ERROR()
#endif

#define SCALE (4)

static int count = 0;

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
    ImGuiApplication::ImGuiApplication(Ref<Window> window, bool docking)    
        : window_(window), docking_(docking)
    {
        window_->Init();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        if (docking_)
        {
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        }

        ImGui::StyleColorsDark();

        window_->ImGuiBackendInit(); 
    }

    ImGuiApplication::~ImGuiApplication()
    {
        for (int i=0; i<imguiWindows_.size(); i++)
        {
            imguiWindows_[i]->OnRelease();
        }
        window_->ImGuiBackendRelease();
        ImGui::DestroyContext();
    }

    void ImGuiApplication::AppendThread(Ref<Thread> thread)
    {
        threads_.push_back(thread);
    }

    long long ImGuiApplication::MainLoop(bool testing)
    {
        long long loop = 0;

        WorkPool::Init();
        for (auto thread: threads_)
        {
            thread->Start();
        }

        while (!window_->ShouldClose())
        {
            Timestep ts;
            window_->OnUpdateBegin(ts);

            ERROR();

            if (docking_)
            {
                ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
            }

            for (auto imguiWindow: imguiWindows_)
            {
                imguiWindow->OnUpdate(ts);
            }

            ERROR();

            for (auto thread: threads_)
            {
                ERROR();
                thread->OnUpdate(ts, testing);
            }

            ERROR();
            
            window_->OnUpdateEnd(ts);

            ERROR();
            loop++;
        }


        for (auto thread: threads_)
        {
            thread->Stop();
        }

        WorkPool::Release();
        return loop;
    }

    void ImGuiApplication::AppendWindow(Ref<ImGuiWindow> window)
    {
        window->OnInit();
        imguiWindows_.push_back(window);
    }
} // namespace ntt
