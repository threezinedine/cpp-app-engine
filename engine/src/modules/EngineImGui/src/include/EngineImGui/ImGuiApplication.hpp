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
            void AppendWorkPool(Ref<WorkPool> workPool);
            Ref<WorkPool> GetWorkPool(const char* name);

        private:
            bool docking_ = false;
            Ref<Window> window_;
            std::vector<Ref<ImGuiWindow>> imguiWindows_;
            std::vector<Ref<Thread>> threads_;
            std::map<std::string, Ref<WorkPool>> workPools_;
    }; 
} // namespace ntt
