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
            void OnUpdate(Timestep ts);
            void AppendComponent(Ref<ImGuiComponent> component);

            static Ref<ImGuiWindow> CreateRef(const char* title);

        private:
            std::vector<Ref<ImGuiComponent>> components_;
    };
} // namespace ntt
