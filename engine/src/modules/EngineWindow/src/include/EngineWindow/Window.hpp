#pragma once
#include "EngineCores/Timestep.hpp"


namespace ntt
{
    class Window
    {
        public:
            virtual void Init() = 0;
            virtual void ImGuiBackendInit() = 0;
            virtual void OnUpdateBegin(Timestep ts) = 0;
            virtual void OnUpdateEnd(Timestep ts) = 0;
            virtual void Release() = 0;
            virtual void ImGuiBackendRelease() = 0;
            virtual bool ShouldClose() = 0;
    }; 
} // namespace ntt
