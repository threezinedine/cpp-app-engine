#pragma once
#include <vector>
#include "EngineCores/EngineCores.hpp"


namespace ntt
{
    class Timestep;
    class ImGuiComponent;

    class ImGuiWindow
    {
        public:
            ImGuiWindow(const char* title);
            virtual ~ImGuiWindow() = default;

            virtual void OnUpdate(Timestep ts);
            virtual void OnUpdateImpl(Timestep ts) = 0;

        private:
            const char* title_;
    };
} // namespace ntt
