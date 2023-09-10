#pragma once
#include <memory>


namespace ntt
{
    class Window;
    class Application;

    class ApplicationBuilder
    {
        public:
            ApplicationBuilder();
            ApplicationBuilder(const ApplicationBuilder& builder);

            ~ApplicationBuilder();

            ApplicationBuilder& UseWindow(std::shared_ptr<Window> window);

            Application Build();

        private:
            std::shared_ptr<Window> window_;
    }; 
} // namespace ntt
