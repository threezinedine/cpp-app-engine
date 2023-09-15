#pragma once

namespace ntt
{
    class Timestep;

    class ImGuiComponent
    {
        public:
            virtual void OnUpdate(Timestep ts) = 0;
    }; 
} // namespace ntt
