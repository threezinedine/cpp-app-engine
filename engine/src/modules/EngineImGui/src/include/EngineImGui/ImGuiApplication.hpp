#pragma once
#include <vector>
#include <map>

#include "EngineCores/EngineCores.hpp"


namespace ntt
{
    class Window;
    class ImGuiWindow;
    class Thread;
    class WorkPool;

    class ImGuiApplication
    {
        public:
            ImGuiApplication(Ref<Window> window, bool docking);
            ~ImGuiApplication();

            long long MainLoop(bool testing = false);
            void AppendWindow(Ref<ImGuiWindow> window);
            void AppendThread(Ref<Thread> thread);
            Ref<WorkPool> GetWorkPool(const char* name);

        private:
            bool docking_ = false;
            Ref<Window> window_;
            std::vector<Ref<ImGuiWindow>> imguiWindows_;
            std::vector<Ref<Thread>> threads_;
    }; 
} // namespace ntt
