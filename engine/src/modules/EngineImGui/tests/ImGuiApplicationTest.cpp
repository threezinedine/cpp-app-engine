#include "PreInclude.hpp"

#include "EngineImGui/ImGuiApplication.hpp"
#include "EngineWindow/EngineWindow.hpp"
#include "EngineWindow/mocking/WindowMocking.hpp"

#include <imgui.h>


TEST(ImGuiApplicationTest, WhenInitializeImGuiApplicationAlsoInitializeWindow)
{
    auto window = WindowMocking::CreateRef();

    EXPECT_CALL(*window, Init()).Times(1);

    {
        ntt::ImGuiApplication imguiApplication(window);
        ASSERT_THAT(ImGui::GetCurrentContext(), ::testing::NotNull());
    }
    
    ASSERT_THAT(ImGui::GetCurrentContext(), ::testing::IsNull());
}