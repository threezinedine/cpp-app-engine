#pragma once
#include <memory>


namespace ntt
{
    class Window;

    class Application
    {
        public:
            Application(std::shared_ptr<Window> window);
            Application(const Application& application);
            ~Application();

        private:
            std::shared_ptr<Window> window_;
    };
} // namespace ntt
