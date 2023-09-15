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
        if (ImGui::Begin(title_))
        {
            OnUpdateImpl(ts);
        }
    }
} // namespace ntt
