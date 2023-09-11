#include "./PreInclude.hpp"

#include "EngineWindow/EngineWindow.hpp"


TEST(WindowTest, WhenInitializeTheWindow)
{
    ntt::WindowImpl window;

    window.Init();

    window.Release();
}