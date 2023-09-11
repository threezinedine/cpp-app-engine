#pragma once
#include "EngineCores/Timestep.hpp"


namespace ntt
{
    class Window
    {
        public:
            virtual void Init() = 0;
            virtual void OnUpdate(Timestep ts) = 0;
            virtual void Release() = 0;
    }; 
} // namespace ntt
