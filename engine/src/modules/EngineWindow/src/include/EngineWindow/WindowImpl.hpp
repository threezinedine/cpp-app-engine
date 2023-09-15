#pragma once

#include "Window.hpp"
#include "EngineCores/EngineCores.hpp"

class GLFWwindow;

namespace ntt
{
    class Timestep;

    class WindowImpl: public Window
    {
        public:
            WindowImpl(int width, int height, const char* title);
            WindowImpl(const char* title);
            ~WindowImpl();

            void Init() override;
            void ImGuiBackendInit() override;
            void OnUpdateBegin(Timestep ts) override;
            void OnUpdateEnd(Timestep ts) override;
            void Release() override;
            void ImGuiBackendRelease() override;
            bool ShouldClose() override;

            static Ref<Window> CreateRef(int width, int height, const char* title);
            static Ref<Window> CreateRef(const char* title);

        private:
            int width_ = -1;
            int height_ = -1;
            const char* title_;
            GLFWwindow* window_;
    };
} // namespace ntt
