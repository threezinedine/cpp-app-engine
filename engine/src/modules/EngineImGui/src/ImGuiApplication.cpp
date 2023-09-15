#include "EngineImGui/PreInclude.hpp"
#include "EngineImGui/ImGuiApplication.hpp"
#include "EngineWindow/EngineWindow.hpp"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include "EngineImGui/ImGuiWindow.hpp"


namespace ntt
{
    ImGuiApplication::ImGuiApplication(Ref<Window> window)    
        : window_(window)
    {
        window_->Init();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        ImGui::StyleColorsDark();

        window_->ImGuiBackendInit(); 
    }

    ImGuiApplication::~ImGuiApplication()
    {
        window_->ImGuiBackendRelease();
        ImGui::DestroyContext();
    }

    long long ImGuiApplication::MainLoop()
    {
        long long loop = 0;

        while (!window_->ShouldClose())
        {
            Timestep ts;
            window_->OnUpdateBegin(ts);
            
            for (auto imguiWindow: imguiWindows_)
            {
                imguiWindow->OnUpdate(ts);
            }
            
            window_->OnUpdateEnd(ts);
            loop++;
        }

        return loop;
    }

    void ImGuiApplication::AppendWindow(Ref<ImGuiWindow> window)
    {
        imguiWindows_.push_back(window);
    }
} // namespace ntt
