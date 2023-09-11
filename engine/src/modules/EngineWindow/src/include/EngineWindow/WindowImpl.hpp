#pragma once

#include "Window.hpp"


namespace ntt
{
    class Timestep;

    class WindowImpl: public Window
    {
        public:
            void Init() override;
            void OnUpdate(Timestep ts) override;
            void Release() override;
    };
} // namespace ntt
