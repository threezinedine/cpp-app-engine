#pragma once
#include "EngineImGui/EngineImGui.hpp"


namespace ntt
{
    class Timestep;

    class DemoWindow: public ImGuiWindow
    {
        public:
            DemoWindow();
            ~DemoWindow();

            virtual void OnUpdate(Timestep ts) override;

        private:
            bool isShow_ = false;
    };
} // namespace ntt
