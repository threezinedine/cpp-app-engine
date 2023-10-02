#include "EngineSupportWindows/PreInclude.hpp"
#include "EngineSupportWindows/DemoWindow.hpp"


namespace ntt
{
    DemoWindow::DemoWindow()
        : ImGuiWindow("Demo Window")
    {

    }  

    DemoWindow::~DemoWindow()
    {

    }

    void DemoWindow::OnUpdate(Timestep ts)
    {
        ImGui::ShowDemoWindow(&isShow_);
    }
} // namespace ntt
