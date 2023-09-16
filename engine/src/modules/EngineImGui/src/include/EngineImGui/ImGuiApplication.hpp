#pragma once
#include <vector>

#include "EngineCores/EngineCores.hpp"


namespace ntt
{
    class Window;
    class ImGuiWindow;

    class ImGuiApplication
    {
        public:
            ImGuiApplication(Ref<Window> window, bool docking);
            ~ImGuiApplication();

            long long MainLoop();
            void AppendWindow(Ref<ImGuiWindow> window);

        private:
            bool docking_ = false;
            Ref<Window> window_;
            std::vector<Ref<ImGuiWindow>> imguiWindows_;
    }; 
} // namespace ntt
