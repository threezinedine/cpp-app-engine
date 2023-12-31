#include "EngineImGui/PreInclude.hpp"
#include "EngineImGui/ImGuiWindow.hpp"

#include <imgui.h>


namespace ntt
{
    ImGuiWindow::ImGuiWindow(const char* title)
        : title_(title)
    {

    }

    void ImGuiWindow::OnUpdate(Timestep ts)
    {
        ImGui::Begin(title_);
        OnUpdateImpl(ts);
        ImGui::End();
    }

    void ImGuiWindow::OnUpdateImpl(Timestep ts)
    {

    }

    void ImGuiWindow::OnInit()
    {

    }

    void ImGuiWindow::OnRelease()
    {

    }
} // namespace ntt
