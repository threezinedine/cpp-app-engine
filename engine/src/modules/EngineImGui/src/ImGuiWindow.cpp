#include "EngineImGui/PreInclude.hpp"
#include "EngineImGui/ImGuiWindow.hpp"
#include "EngineImGui/ImGuiComponent.hpp"


namespace ntt
{
    void ImGuiWindow::OnUpdate(Timestep ts)
    {
        for (auto component: components_)
        {
            component->OnUpdate(ts);
        }
    }

    void ImGuiWindow::AppendComponent(Ref<ImGuiComponent> component)
    {
        components_.push_back(component);
    }

    Ref<ImGuiWindow> ImGuiWindow::CreateRef(const char* title)
    {
        return std::make_unique<ImGuiWindow>();
    } 
} // namespace ntt
