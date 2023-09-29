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
                name_("Name", 
                    "C:/Users/Acer/OneDrive - Hanoi University of Science and Technology/Pictures/Game/FlappyBird/bird.png"),
                size_("Image Size", { 500, 350 }, 100, 1000)
        {
            image_ = std::make_shared<ntt::Image>("Image", 300, 300);
            imageDisplay_ = std::make_unique<ntt::ImGuiImage>(image_);
        }

        void OnInit() override
        {
            image_->Init();
            image_->SetSize(400, 300);
            image_->FromFile(name_.Value());
            imageDisplay_->Init();
            // imageDisplay_.SetImage(image_->Value());
        }

        void OnUpdateImpl(ntt::Timestep ts) override
        {
            ImGui::Text("Test Window");

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

            ntt::StringOptions options{ 
                .fileOpts = { 
                    .types = ".png,.jpg", 
                    .title = "Choose image file", 
                    .path = "C:/Users/Acer/Downloads/", 
                } 
            };
            ImGui::Text(name_.ToString().c_str());
            if (name_.OnUpdate(ts, ntt::FILE_DIALOG, (void*)&options))
            {
                image_->FromFile(name_.Value());
            }

            size_.OnUpdate(ts, ntt::SLIDER);

            imageDisplay_->OnUpdate({ size_.Value()[0], size_.Value()[1] });
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
        ntt::Array<int, 2> size_;
        ntt::Ref<ntt::Image> image_;
        ntt::Scope<ntt::ImGuiImage> imageDisplay_;
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