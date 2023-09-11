#include "EngineImGui/PreInclude.hpp"
#include "EngineImGui/ImGuiApplication.hpp"
#include "EngineWindow/EngineWindow.hpp"
#include <imgui.h>


namespace ntt
{
    ImGuiApplication::ImGuiApplication(Ref<Window> window)    
        : window_(window)
    {
        window_->Init();
        ImGui::CreateContext();
    }

    ImGuiApplication::~ImGuiApplication()
    {
        ImGui::DestroyContext();
    }
} // namespace ntt
