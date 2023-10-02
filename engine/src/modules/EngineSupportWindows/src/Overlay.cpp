#include "EngineSupportWindows/PreInclude.hpp"
#include "EngineSupportWindows/Overlay.hpp"


namespace ntt
{
    Overlay::Overlay(const char* name, std::function<void()> func, OverlayLocation location)
        : ImGuiWindow(name), location_(location), func_(func), open_(true)
    {
        
    } 

    Overlay::~Overlay()
    {
        
    } 

    void Overlay::OnUpdate(Timestep ts)
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
        if (location_ >= 0)
        {
            const float PAD = 10.0f;
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
            ImVec2 work_size = viewport->WorkSize;
            ImVec2 window_pos, window_pos_pivot;
            window_pos.x = (location_ & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
            window_pos.y = (location_ & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
            window_pos_pivot.x = (location_ & 1) ? 1.0f : 0.0f;
            window_pos_pivot.y = (location_ & 2) ? 1.0f : 0.0f;
            ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
            ImGui::SetNextWindowViewport(viewport->ID);
            window_flags |= ImGuiWindowFlags_NoMove;
        }
        else if (location_ == -2)
        {
            ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
            window_flags |= ImGuiWindowFlags_NoMove;
        }
        ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
        if (ImGui::Begin(title_, &open_, window_flags))
        {
            func_();
            if (ImGui::BeginPopupContextWindow())
            {
                if (ImGui::MenuItem("Custom",       NULL, location_ == -1)) location_ = -1;
                if (ImGui::MenuItem("Center",       NULL, location_ == -2)) location_ = -2;
                if (ImGui::MenuItem("Top-left",     NULL, location_ == 0)) location_ = 0;
                if (ImGui::MenuItem("Top-right",    NULL, location_ == 1)) location_ = 1;
                if (ImGui::MenuItem("Bottom-left",  NULL, location_ == 2)) location_ = 2;
                if (ImGui::MenuItem("Bottom-right", NULL, location_ == 3)) location_ = 3;
                if (open_ && ImGui::MenuItem("Close")) open_ = false;
                ImGui::EndPopup();
            }
        }
        ImGui::End();
        }
} // namespace ntt
