#include "PreInclude.hpp"

#include "EngineImGui/ImGuiApplication.hpp"
#include "EngineImGui/ImGuiWindow.hpp"
#include "EngineImgui/ImGuiApplicationBuilder.hpp"
#include "EngineCores/EngineCores.hpp"
#include "EngineWindow/EngineWindow.hpp"
#include "EngineWindow/mocking/WindowMocking.hpp"
#include "EngineThreading/mock/ThreadMock.hpp"
#include "EngineExceptions/EngineExceptions.hpp"

#include <imgui.h>


class ImGuiWindowMock: public ntt::ImGuiWindow
{
    public:
        ImGuiWindowMock(const char* title)
            : ImGuiWindow(title) {}

        MOCK_METHOD(void, OnInit, (), (override));
        MOCK_METHOD(void, OnUpdate, (ntt::Timestep), (override));
        MOCK_METHOD(void, OnUpdateImpl, (ntt::Timestep), (override));
        MOCK_METHOD(void, OnRelease, (), (override));

        static ntt::Ref<ImGuiWindowMock> CreateRef()
        {
            return std::make_shared<ImGuiWindowMock>("Testing window");
        }
};


class ImGuiApplicationTest: public testing::Test
{
    protected:
        ntt::Ref<WindowMocking> window_;
        ntt::Ref<ThreadMock> thread_;

        void SetUp() override
        {
            window_ = WindowMocking::CreateRef(); 
            thread_ = ThreadMock::CreateRef(0);

            thread_->IgnoreSetRunning();
            thread_->IgnoreOnRunImpl();
        }
};


TEST_F(ImGuiApplicationTest, WhenInitializeImGuiApplicationAlsoInitializeWindow)
{
    EXPECT_CALL(*window_, Init()).Times(1);
    EXPECT_CALL(*window_, ImGuiBackendInit()).Times(1);
    EXPECT_CALL(*window_, ImGuiBackendRelease()).Times(1);
    window_->WindowShouldCloseAfter(5);

    EXPECT_CALL(*window_, OnUpdateBegin(testing::_)).Times(5);
    EXPECT_CALL(*window_, OnUpdateEnd(testing::_)).Times(5);

    {
        ntt::ImGuiApplication imguiApplication(window_, false);
        ASSERT_THAT(ImGui::GetCurrentContext(), ::testing::NotNull());

        long long loop = imguiApplication.MainLoop();

        EXPECT_THAT(loop, testing::Eq(5));
    }
    
    ASSERT_THAT(ImGui::GetCurrentContext(), ::testing::IsNull());
}

TEST_F(ImGuiApplicationTest, GivenAddingANewImGuiApplicationWindowWhenRunOnUpdateThenOnUpdateWillBeCalled)
{
    window_->IgnoreMocking();
    window_->WindowShouldCloseAfter(5);
    thread_->SetupIsRunningReturnFalseAt(8);

    auto imguiWindow = ImGuiWindowMock::CreateRef();
    EXPECT_CALL(*imguiWindow, OnInit()).Times(1);
    EXPECT_CALL(*imguiWindow, OnUpdate(testing::_)).Times(5);
    EXPECT_CALL(*imguiWindow, OnRelease()).Times(1);

    EXPECT_CALL(*thread_, StartImpl()).Times(1);
    EXPECT_CALL(*thread_, StopImpl()).Times(1);

    {
        ntt::Ref<ntt::ImGuiApplication> application = ntt::ImGuiApplicationBuilder()
                                                .UseWindow(window_)
                                                .AddImGuiWindow(imguiWindow)
                                                .AddThread(thread_)
                                                .Build();

        application->MainLoop();
    }
}

TEST_F(ImGuiApplicationTest, WhenCreateApplicationWithoutWindowThenThrowError)
{
    EXPECT_THROW(auto application = ntt::ImGuiApplicationBuilder()
                        .Build(),
        ntt::ImGuiApplicationConfigErrorException
    );
}