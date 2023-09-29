#include "CameraThread.hpp"
#include "AppEngine/AppEngine.hpp"


int main(void)
{
    ntt::Ref<ntt::Window> window = ntt::WindowImpl::CreateRef("Test window");
    ntt::Ref<ntt::Thread> thread = CameraThread::CreateRef();

    auto application = ntt::ImGuiApplicationBuilder()
                            .UseWindow(window)
                            .AddThread(thread)
                            .UseDocking()
                            .Build();

    application->MainLoop();

    return 0;
}