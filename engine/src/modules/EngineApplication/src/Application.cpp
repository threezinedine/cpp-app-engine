#include "EngineApplication/PreInclude.hpp"
#include "EngineApplication/Application.hpp"
#include "EngineWindow/Window.hpp"


namespace ntt
{
    Application::Application(Ref<Window> window)
        : window_(window)
    {
        window->Init();
    }

    Application::Application(const Application& application)
    {

    }

    Application::~Application()
    {
        window_->Release();
    }

    void Application::OnUpdate()
    {
        window_->OnUpdate();
    }
} // namespace ntt
