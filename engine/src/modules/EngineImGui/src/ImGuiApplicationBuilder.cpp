#include "EngineImgui/PreInclude.hpp"
#include "EngineImgui/ImGuiApplicationBuilder.hpp"
#include "EngineImgui/ImGuiApplication.hpp"
#include "EngineExceptions/EngineExceptions.hpp"


namespace ntt
{
    ImGuiApplicationBuilder::ImGuiApplicationBuilder()
    {

    };    

    ImGuiApplicationBuilder::ImGuiApplicationBuilder(const ImGuiApplicationBuilder& other)
    {

    }

    ImGuiApplicationBuilder::~ImGuiApplicationBuilder()
    {

    }

    ImGuiApplicationBuilder& ImGuiApplicationBuilder::UseWindow(Ref<Window> window)
    {
        window_ = window;
        return *this;
    }

    ImGuiApplicationBuilder& ImGuiApplicationBuilder::AddImGuiWindow(Ref<ImGuiWindow> imguiWindow)
    {
        imguiWindows_.push_back(imguiWindow);
        return *this;
    }

    Ref<ImGuiApplication> ImGuiApplicationBuilder::Build()
    {
        if (window_ == nullptr)
        {
            throw ImGuiApplicationConfigErrorException("Window is not set.");
        }

        auto imguiApplication = std::make_shared<ImGuiApplication>(window_);

        for (auto imguiWindow: imguiWindows_)
        {
            imguiApplication->AppendWindow(imguiWindow);
        }

        return imguiApplication;
    }

} // namespace ntt