#pragma once
#include <vector>

#include "EngineCores/EngineCores.hpp"


namespace ntt
{
    class Window;
    class ImGuiWindow;
    class Thread;

    class ImGuiApplication
    {
        public:
            ImGuiApplication(Ref<Window> window, bool docking);
            ~ImGuiApplication();

            long long MainLoop();
            void AppendWindow(Ref<ImGuiWindow> window);
            void AppendThread(Ref<Thread> thread);

        private:
            bool docking_ = false;
            Ref<Window> window_;
            std::vector<Ref<ImGuiWindow>> imguiWindows_;
            std::vector<Ref<Thread>> threads_;
    }; 
} // namespace ntt
