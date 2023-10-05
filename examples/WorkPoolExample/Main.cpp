#include "AppEngine/AppEngine.hpp"


class DataWindow: public ntt::ImGuiWindow
{
    public:
        DataWindow(const char* name)
            : ntt::ImGuiWindow(name), uart_("UART Connection")
        {
            value_ = std::make_unique<ntt::Bool>("Value");
        }

        ~DataWindow()
        {

        }

        void OnUpdateImpl(ntt::Timestep ts)
        {
            uart_.OnUpdate(ts);

            if (ImGui::Button("Toggle"))
            {
                value_->SetValue(!value_->Value());
            }

            ImGui::Text(value_->ToString().c_str());
        }

    private:
        ntt::Scope<ntt::Bool> value_;
        ntt::UARTConnection uart_;
};


int main(void)
{
    auto window = ntt::WindowImpl::CreateRef("COM Work Pool Example");
    auto imguiWindow = std::make_shared<DataWindow>("Data Window");

    auto application = ntt::ImGuiApplicationBuilder()   
                            .UseWindow(window)
                            .AddImGuiWindow(imguiWindow)
                            .AddWorkPool(
                                ntt::WorkPool::CreateRef("COM Work Pool")
                            )
                            .UseDocking()
                            .Build();

    application->MainLoop();

    return 0;
}