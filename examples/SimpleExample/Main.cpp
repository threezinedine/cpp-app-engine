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
                color_("Color", { 0, 0, 0, 0 }, 0, 255),
                speed_("Speed", 0, 0, 10),
                color3_("Color3", { 0, 0, 0 }, 0.0f, 1.0f),
                getData_("GetData"),
                name_("Name")
        {

        }

        void OnUpdateImpl(ntt::Timestep ts) override
        {
            ImGui::Text("Test Window");

            static bool showWindow = true;
            ImGui::ShowDemoWindow(&showWindow);

            scores_.OnUpdate(ts, ntt::SLIDER);

            ntt::DataOptions<int> scoresOptions { .choices = { {"FIRST_CHILD", 1}, {"SECOND_CHILD", 3}}};
            scores_.OnUpdate(ts, ntt::WITH_CHOICES, (void*)&scoresOptions);

            position_.OnUpdate(ts, ntt::SLIDER);
            position3D_.OnUpdate(ts, ntt::SLIDER);
            color_.OnUpdate(ts, ntt::SLIDER);

            speed_.OnUpdate(ts, ntt::SLIDER);

            color3_.OnUpdate(ts, ntt::COLOR_PICKER);

            ImGui::Text(color3_.ToString().c_str());

            getData_.OnUpdate(ts);
            ImGui::Text(getData_.ToString().c_str());

            ntt::StringOptions options{ .choices = { "Hello", "Test" } };
            name_.OnUpdate(ts, ntt::FILE_DIALOG);
            ImGui::Text(name_.ToString().c_str());
        }

    private:
        ntt::Data<int> scores_;
        ntt::Data<float> speed_;
        ntt::Array<int, 2> position_;
        ntt::Array<int, 3> position3D_;
        ntt::Array<int, 4> color_;
        ntt::Array<float, 3> color3_;
        ntt::Bool getData_;
        ntt::String<256> name_;
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