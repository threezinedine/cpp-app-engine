#include "EngineImGui/PreInclude.hpp"
#include "EngineImGui/ImGuiApplication.hpp"
#include "EngineWindow/EngineWindow.hpp"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include "EngineImGui/ImGuiWindow.hpp"
#include "EngineThreading/EngineThreading.hpp"

#include <iostream>


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

    long long ImGuiApplication::MainLoop()
    {
        long long loop = 0;

        for (auto thread: threads_)
        {
            thread->Start();
        }

        while (!window_->ShouldClose())
        {
            Timestep ts;
            window_->OnUpdateBegin(ts);

            if (docking_)
            {
                ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
            }
            
            for (auto imguiWindow: imguiWindows_)
            {
                imguiWindow->OnUpdate(ts);
            }
            
            window_->OnUpdateEnd(ts);
            loop++;
        }

        for (auto thread: threads_)
        {
            thread->Stop();
        }

        return loop;
    }

    void ImGuiApplication::AppendWindow(Ref<ImGuiWindow> window)
    {
        window->OnInit();
        imguiWindows_.push_back(window);
    }
} // namespace ntt
