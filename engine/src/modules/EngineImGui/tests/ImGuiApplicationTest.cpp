#include "PreInclude.hpp"

#include "EngineImGui/ImGuiApplication.hpp"
#include "EngineImGui/ImGuiWindow.hpp"
#include "EngineCores/EngineCores.hpp"
#include "EngineWindow/EngineWindow.hpp"
#include "EngineWindow/mocking/WindowMocking.hpp"

#include <imgui.h>


class ImGuiWindowMock: public ntt::ImGuiWindow
{
    public:
        ImGuiWindowMock(const char* title)
            : ImGuiWindow(title) {}

        MOCK_METHOD(void, OnUpdate, (ntt::Timestep), (override));
        MOCK_METHOD(void, OnUpdateImpl, (ntt::Timestep), (override));

        static ntt::Ref<ImGuiWindowMock> CreateRef()
        {
            return std::make_shared<ImGuiWindowMock>("Testing window");
        }
};


class ImGuiApplicationTest: public testing::Test
{
    protected:
        ntt::Ref<WindowMocking> window_;

        void SetUp() override
        {
            window_ = WindowMocking::CreateRef(); 
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
        ntt::ImGuiApplication imguiApplication(window_);
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

    ntt::ImGuiApplication application(window_);
    auto imguiWindow = ImGuiWindowMock::CreateRef();

    EXPECT_CALL(*imguiWindow, OnUpdate(testing::_)).Times(5);

    application.AppendWindow(imguiWindow);

    application.MainLoop();
}