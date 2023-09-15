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

    long long Application::MainLoop()
    {
        long long loop = 0;

        while (!window_->ShouldClose())
        {
            Timestep ts;
            window_->OnUpdateBegin(ts);
            window_->OnUpdateEnd(ts);
            loop++;
        }

        return loop;
    }
} // namespace ntt
