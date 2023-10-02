#pragma once

#include "EngineImGui/EngineImGui.hpp"
#include <functional>


namespace ntt
{
    enum OverlayLocation
    {
        CENTER          = -2,
        CUSTOM          = -1,
        TOP_LEFT        = 0,
        TOP_RIGHT       = 1,
        BOTTOM_LEFT     = 2,
        BOTTOM_RIGHT    = 3,
    };

    class Overlay: public ImGuiWindow
    {
        public:
            Overlay(const char* name, std::function<void()> func, OverlayLocation location = TOP_LEFT);
            ~Overlay();

            virtual void OnUpdate(Timestep ts) override;

        protected:
            int location_;
            std::function<void()> func_;
            bool open_;
    };
} // namespace ntt
