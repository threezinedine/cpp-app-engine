#pragma once
#include <vector>
#include "EngineCores/EngineCores.hpp"

namespace ntt
{
    class Window;
    class ImGuiApplication;
    class ImGuiWindow;

    class ImGuiApplicationBuilder
    {
        public:
            ImGuiApplicationBuilder();
            ImGuiApplicationBuilder(const ImGuiApplicationBuilder& other);
            ~ImGuiApplicationBuilder();

            ImGuiApplicationBuilder& UseWindow(Ref<Window> window);
            ImGuiApplicationBuilder& AddImGuiWindow(Ref<ImGuiWindow> imguiWindow);
            ImGuiApplicationBuilder& UseDocking();
            Ref<ImGuiApplication> Build();

        private:
            Ref<Window> window_;
            std::vector<Ref<ImGuiWindow>> imguiWindows_;
            bool docking_ = false;
    }; 
} // namespace ntt
