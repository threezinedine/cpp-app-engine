#include "AppEngine/AppEngine.hpp"

int main(void)
{
    ntt::Ref<ntt::Window> window = ntt::WindowImpl::CreateRef("Test window");

    auto application = ntt::ApplicationBuilder()
                            .UseWindow(window)
                            .Build();

    application.MainLoop();

    return 0;
}