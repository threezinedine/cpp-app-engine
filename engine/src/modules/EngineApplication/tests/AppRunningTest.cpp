#include "PreInclude.hpp"

#include "EngineApplication/EngineApplication.hpp"
#include "EngineExceptions/EngineExceptions.hpp"
#include "EngineWindow/EngineWindow.hpp"
#include "EngineWindow/mocking/WindowMocking.hpp"


TEST(AppRunningTest, WhenInitializeTheApplicationThenTheWindowIsAlsoInitialized)
{
    ntt::Ref<WindowMocking> window = WindowMocking::CreateRef();

    auto builder = ntt::ApplicationBuilder()
                    .UseWindow(window);

    EXPECT_CALL(*window, Init()).Times(1);
    EXPECT_CALL(*window, OnUpdate(testing::_)).Times(1);
    EXPECT_CALL(*window, Release()).Times(1);

    {
        auto application = builder.Build();

        application.OnUpdate();
    }
}

TEST(AppRunningTest, WhenInitializeTheApplicationWithoutTheWindowThenThrowException)
{
    auto builder = ntt::ApplicationBuilder();

    EXPECT_THROW(builder.Build(), ntt::ApplicationConfigErrorException);
}