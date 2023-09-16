#include "AppEngine/AppEngine.hpp"
#include <imgui.h>


class TestWindow: public ntt::ImGuiWindow
{
    public:
        TestWindow()
            : ntt::ImGuiWindow("Test Window"), scores_("Scores")
        {

        }

        void OnUpdateImpl(ntt::Timestep ts) override
        {
            ImGui::Text("Test Window");

            static bool showWindow = true;
            ImGui::ShowDemoWindow(&showWindow);

            scores_.OnUpdate(ts, ntt::SLIDER);
        }

    private:
        ntt::Integer scores_;
};


int main(void)
{
    ntt::Ref<ntt::Window> window = ntt::WindowImpl::CreateRef("Test window");

    auto application = ntt::ImGuiApplicationBuilder()
                            .UseWindow(window)
                            .AddImGuiWindow(std::make_shared<TestWindow>())
                            .UseDocking()
                            .Build();

    application->MainLoop();

    return 0;
}