#pragma once
#include "EngineCores/ScopeDefinition.hpp"


namespace ntt
{
    class Window;

    class Application
    {
        public:
            Application(Ref<Window> window);
            Application(const Application& application);
            ~Application();

            long long MainLoop();

        private:
            Ref<Window> window_;
    };
} // namespace ntt
