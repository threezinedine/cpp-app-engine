#include "EngineImgui/PreInclude.hpp"
#include "EngineImgui/ImGuiApplicationBuilder.hpp"
#include "EngineImgui/ImGuiApplication.hpp"
#include "EngineExceptions/EngineExceptions.hpp"
#include "EngineThreading/EngineThreading.hpp"


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

    ImGuiApplicationBuilder& ImGuiApplicationBuilder::AddThread(Ref<Thread> thread)
    {
        threads_.push_back(thread);
        return *this;
    }

    ImGuiApplicationBuilder& ImGuiApplicationBuilder::AddWorkPool(Ref<WorkPool> workPool)
    {
        workPools_.push_back(workPool);
        return *this;
    }


    ImGuiApplicationBuilder& ImGuiApplicationBuilder::UseDocking()
    {
        docking_ = true;
        return *this;
    }

    Ref<ImGuiApplication> ImGuiApplicationBuilder::Build()
    {
        if (window_ == nullptr)
        {
            throw ImGuiApplicationConfigErrorException("Window is not set.");
        }

        auto imguiApplication = std::make_shared<ImGuiApplication>(window_, docking_);

        for (auto imguiWindow: imguiWindows_)
        {
            imguiApplication->AppendWindow(imguiWindow);
        }

        for (auto thread: threads_)
        {
            imguiApplication->AppendThread(thread);
        }

        for (auto workPool: workPools_)
        {
            imguiApplication->AppendWorkPool(workPool);
        }

        return imguiApplication;
    }

} // namespace ntt
