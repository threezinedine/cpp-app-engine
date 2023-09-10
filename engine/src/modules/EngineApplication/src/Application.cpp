#include "EngineApplication/PreInclude.hpp"
#include "EngineApplication/Application.hpp"
#include "EngineWindow/Window.hpp"


namespace ntt
{
    Application::Application(std::shared_ptr<Window> window)
        : window_(window)
    {
        window->Init();
    }

    Application::Application(const Application& application)
    {

    }

    Application::~Application()
    {

    }
} // namespace ntt
