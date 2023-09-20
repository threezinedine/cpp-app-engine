#include "AppEngine/AppEngine.hpp"
#include <imgui.h>
#include <sstream>


class TestWindow: public ntt::ImGuiWindow
{
    public:
        TestWindow()
            : ntt::ImGuiWindow("Test Window"), 
                scores_("Scores"),
                position_("Positions"),
                position3D_("Position 3D", { 0, 0, 0 }, 10, 300),
                color_("Color", { 0, 0, 0, 0 }, 0, 255)
        {

        }

        void OnUpdateImpl(ntt::Timestep ts) override
        {
            ImGui::Text("Test Window");

            static bool showWindow = true;
            ImGui::ShowDemoWindow(&showWindow);

            scores_.OnUpdate(ts, ntt::SLIDER);
            position_.OnUpdate(ts, ntt::INPUT);
            position3D_.OnUpdate(ts, ntt::SLIDER);
            color_.OnUpdate(ts, ntt::SLIDER);
        }

    private:
        ntt::Integer scores_;
        ntt::Integer2 position_;
        ntt::Integer3 position3D_;
        ntt::Integer4 color_;
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