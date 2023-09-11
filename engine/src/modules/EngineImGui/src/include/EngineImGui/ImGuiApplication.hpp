#pragma once

#include "EngineCores/EngineCores.hpp"


namespace ntt
{
    class Window;

    class ImGuiApplication
    {
        public:
            ImGuiApplication(Ref<Window>);
            ~ImGuiApplication();

        private:
            Ref<Window> window_;
    }; 
} // namespace ntt
